#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTimer>

#include "base.h"
#include "data.h"

class Worker : public QObject
{
    Q_OBJECT
private:
    QTimer* timer;
    int n;
    Base* base;
    Data* data;

public:
    Worker(QObject *parent = nullptr);
    ~Worker();

signals:
    void valueChange(int);
    void finished();
    void connected();
    void setStatus(QString);
    void ready();
    void readed();
    void writed();

public slots:
    void slotDoWork();
    void slotMakeConnection();
    void slotPrepareBase(QString);
    void slotRun();

private slots:
    void setNextValue();
};

#endif // WORKER_H
