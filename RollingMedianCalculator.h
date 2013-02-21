#ifndef ROLLINGMEDIANCALCULATOR_H
#define ROLLINGMEDIANCALCULATOR_H

#include <QImage>
#include <QVector>

class RollingMedianCalculator
{
public:
    RollingMedianCalculator();

    QRgb next(const QRgb& value);

private:
    static int decimateByLowestReturnHighest(QVector<quint8>& vec);
    QVector<quint8> _r;
    QVector<quint8> _g;
    QVector<quint8> _b;
};

#endif // ROLLINGMEDIANCALCULATOR_H
