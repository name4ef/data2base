#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QStringList>
#include <QDebug>

class Calculator
{
public:
    Calculator(int s) :
        normalSize(s)
    {}
    void input(QString);
    QString run();

private:
    int normalSize;
    QStringList data;
    bool calc1(); // Calc_zond1 = Zond_5 + Zond_7
    bool calc2(); // Calc_zond2 = Zond_8 * Zond_11
};

#endif // CALCULATOR_H
