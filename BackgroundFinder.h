#ifndef BACKGROUNDFINDER_H
#define BACKGROUNDFINDER_H

#include <QObject>
#include <QImage>
#include <QList>
#include <QVector>

#include "RollingMedianCalculator.h"
#include "RollingAverageCalculator.h"

class BackgroundFinder : public QObject
{
    Q_OBJECT
public:
    explicit BackgroundFinder(QObject *parent = 0);

    const QImage& background() const;
    
signals:
    
public slots:
    void reset();
    void addFrame(const QImage& img);

private:
    QVector<RollingMedianCalculator> _rolling;
    QImage _bg;
};

#endif // BACKGROUNDFINDER_H
