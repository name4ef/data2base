#include "calculator.h"

void Calculator::input(QString s)
{
    data = s.split(",");
    int size = data.size();
    if (data.size() < normalSize) {
        for (int i = 0; i < normalSize-size; ++i) {
            data.append("null");
        }
    }
}

QString Calculator::run()
{
    QString s;
    if (calc1() && calc2()) {
        s = data.join(",");
    } else {
        s.clear();
    }
    return s;
}

bool Calculator::calc1()
{
    float result = data[6].toFloat() + data[8].toFloat();
    data.append(QString::number(result));
    return true;
}

bool Calculator::calc2()
{
    float result = data[9].toFloat() * data[12].toFloat();
    data.append(QString::number(result));
    return true;
}
