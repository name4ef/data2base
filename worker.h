#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QEventLoop>

#include "base.h"
#include "data.h"
#include "calculator.h"

class Worker : public QObject
{
    Q_OBJECT
private:
    Base* base;
    Data* data;
    Calculator* calc;
    bool run;
    QString path;

public:
    Worker(QObject *parent = nullptr);

signals:
    void siConnected();
    void siStatus(QString);
    void siReady();
    void siReaded();
    void siWrited();
    void siTime();
    void siReset();

public slots:
    void slMakeConnection();
    void slNeedBase(QString);
    void slStart();
    void slPause();
    void slStop();
};

#endif // WORKER_H
