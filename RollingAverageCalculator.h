#ifndef ROLLINGAVERAGECALCULATOR_H
#define ROLLINGAVERAGECALCULATOR_H

#include <QtGlobal>
#include <QImage>

class RollingAverageCalculator
{
public:
    RollingAverageCalculator(qreal learningRate = 0.05);

    qreal learningRate() const;
    void setLearningRate(qreal nRate);

    QRgb next(const QRgb& value);

private:
    qreal _learningRate;
    qreal _minusLearningRate;

    qreal _ro;
    qreal _go;
    qreal _bo;
    qreal _vo;

    qreal _uncertainty;
};

#endif // ROLLINGAVERAGECALCULATOR_H
