#include "BackgroundFinder.h"

#include <QtDebug>
#include <QtConcurrentRun>

BackgroundFinder::BackgroundFinder(QObject *parent) :
    QObject(parent)
{
}

const QImage &BackgroundFinder::background() const
{
    return _bg;
}

void BackgroundFinder::reset()
{
    _bg.fill(Qt::white);
    _rolling.clear();
}

void BackgroundFinder::addFrame(const QImage &img)
{
    if (_rolling.isEmpty())
    {
        for (int i = 0; i < img.width() * img.height(); i++)
        {
            _rolling.append(RollingMedianCalculator());
        }
    }


    QVector<QFuture<QRgb> > futures;
    futures.reserve(img.width() * img.height());
    for (int y = 0; y < img.height(); y++)
    {
        for (int x = 0; x < img.width(); x++)
        {
            const int index = y * img.width() + x;
            QFuture<QRgb> future = QtConcurrent::run(&_rolling[index],
                                                     &RollingMedianCalculator::next,
                                                     img.pixel(x,y));
            futures.append(future);
        }
    }

    QImage newBG(img.size(), img.format());
    for (int y = 0; y < img.height(); y++)
    {
        for (int x = 0; x < img.width(); x++)
        {
            const int index = y * img.width() + x;
            futures[index].waitForFinished();
            newBG.setPixel(x,y, futures.at(index).result());
        }
    }

    _bg = newBG;
}
