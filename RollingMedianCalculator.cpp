#include "RollingMedianCalculator.h"

#include <QtDebug>

RollingMedianCalculator::RollingMedianCalculator()
{
    _r.fill(0, 256);
    _g.fill(0, 256);
    _b.fill(0, 256);
}

QRgb RollingMedianCalculator::next(const QRgb &value)
{
    const int red = qRed(value);
    const int green = qGreen(value);
    const int blue = qBlue(value);

    _r[red]++;
    _g[green]++;
    _b[blue]++;

    QRgb toRet = qRgb(this->decimateByLowestReturnHighest(_r),
                      this->decimateByLowestReturnHighest(_g),
                      this->decimateByLowestReturnHighest(_b));

    return toRet;
}

//private
int RollingMedianCalculator::decimateByLowestReturnHighest(QVector<quint8> &vec)
{
    int lowestNonZeroIndex = 0;
    int lowestNonZero = 0;

    int highestIndex = 0;
    int highest = 0;

    for (int i = 0; i < 256; i++)
    {
        quint8 val = vec.at(i);
        if (val < lowestNonZero && val != 0)
        {
            lowestNonZero = val;
            lowestNonZeroIndex = i;
        }

        if (val > highest)
        {
            highest = val;
            highestIndex = i;
        }
    }

    if (lowestNonZero != 0)
    {
        for (int i = 0; i < 256; i++)
        {
            if (vec.at(i) >= lowestNonZero)
                vec[i] -= lowestNonZero;
        }
    }

    return highestIndex;
}
