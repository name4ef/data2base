#include "config.h"

QString Config::get(QString val)
{
    return this->value(val, val).toString();
}
