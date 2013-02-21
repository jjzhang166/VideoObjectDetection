#include "RollingAverageCalculator.h"

#include <QtDebug>

RollingAverageCalculator::RollingAverageCalculator(qreal learningRate) :
    _learningRate(learningRate),
    _minusLearningRate(1.0 - learningRate),
    _ro(0.5), _go(0.5), _bo(0.5), _vo(0.5),
    _uncertainty(0.0)
{
    //qDebug() << _learningRate << _minusLearningRate;
}

qreal RollingAverageCalculator::learningRate() const
{
    return _learningRate;
}

void RollingAverageCalculator::setLearningRate(qreal nRate)
{
    _learningRate = nRate;
}

QRgb RollingAverageCalculator::next(const QRgb &value)
{
    const qreal r = (qreal)qRed(value) / 255.0;
    const qreal g = (qreal)qGreen(value) / 255.0;
    const qreal b = (qreal)qBlue(value) / 255.0;
    const qreal v = (qreal)qGray(value) / 255.0;

    const qreal diff = qAbs<qreal>(v - _vo);

    const qreal cLR = 0.05;
    const qreal mcLR = 1.0 - cLR;
    _uncertainty = cLR * diff + mcLR * _uncertainty;

    const qreal lr = qMax<qreal>(0.0, qMin<qreal>(1.0, _learningRate + _uncertainty));
    const qreal mlr = 1.0 - lr;

    _ro = lr * r + mlr * _ro;
    _go = lr * g + mlr * _go;
    _bo = lr * b + mlr * _bo;
    _vo = lr * v + mlr * _vo;

    return qRgb(_ro * 255.0, _go * 255.0, _bo * 255.0);
}
