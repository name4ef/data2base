#include "worker.h"

Worker::Worker(QObject *parent) :
    QObject(parent),
    n(0)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(setNextValue()));
}

Worker::~Worker()
{
    delete data;
    delete base;
}

void Worker::slotMakeConnection()
{
    base = new Base();
    if (base->connect()) {
        emit connected();
    }
}

void Worker::slotPrepareBase(QString path)
{
    data = new Data(path);
    bool prepared = base->prepareBase(data->getFileName(), data->getFirstLine());
    if (prepared) {
        emit ready();
    }
}

void Worker::slotRun()
{
    for (;;) {
        QString line = data->getLine();
        if (line.length() > 0) { // TODO check for valid
            emit readed();
            if (base->insertRow(line)) {
                emit writed();
            } else {
                qDebug() << "Error of write";
                break;
            }
        } else {
            qDebug() << "Error of read. Readed line: " + line;
            break;
        }
    }
}

void Worker::slotDoWork()
{
    timer->start(50);
}

void Worker::setNextValue()
{
    emit valueChange(++n);
    if (n > 3600) {
        timer->stop();
        emit finished();
    }
}
