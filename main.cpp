#include "application.h"
#include "dialog.h"
#include "base.h"
#include "data.h"

int main(int argc, char *argv[])
{
    Application a(argc, argv);
    Dialog d;
    Data data;
    Base base;

    QObject::connect(&base, SIGNAL(status(QString)),
                     &d, SLOT(setStatus(QString))
                     );
    QObject::connect(&base, SIGNAL(connected()),
                     &d, SLOT(setConnected())
                     );
    QObject::connect(&base, SIGNAL(ready()),
                     &d, SLOT(setReady())
                     );
    QObject::connect(&data, SIGNAL(waitBase(QString, QStringList)),
                     &base, SLOT(prepareBase(QString, QStringList))
                     );
    QObject::connect(&d, SIGNAL(getFirstLine(QString)),
                     &data, SLOT(getFirstLine(QString))
                     );

    d.show();
    base.start();
    data.start();

    int r = a.exec();
    base.quit();
    data.quit();
    base.wait();
    data.wait();
    return r;
}
