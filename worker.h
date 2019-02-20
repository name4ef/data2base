#ifndef WORKER_H
#define WORKER_H

#include <QObject>

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

public:
    Worker(QObject *parent = nullptr);
    ~Worker();

signals:
    void connected();
    void status(QString);
    void ready();
    void readed();
    void writed();

public slots:
    void slotMakeConnection();
    void slotPrepareBase(QString);
    void slotRun();
};

#endif // WORKER_H
