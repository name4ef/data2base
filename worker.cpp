#include "worker.h"

Worker::Worker(QObject *parent) :
    QObject(parent),
    run(false)
{}

void Worker::slMakeConnection()
{
    base = new Base();
    emit siStatus("connecting to dbms...");
    if (base->connect()) {
        emit siConnected();
    } else {
        emit siStatus("can't connect to dbms");
    }
}

void Worker::slNeedBase(QString p)
{
    path = p;
    data = new Data(path);
    QString header = data->getFirstLine();
    QStringList headers = header.split(",");
    calc = new Calculator(headers.count());
    headers.append("Calc_zond1");
    headers.append("Calc_zond2");
    if (base->prepareBase(data->getFileName(), headers)) {
        emit siReady();
    }
}

void Worker::slStart()
{
    run = true;
    for (int i = 0; run; ++i) {
        QString line = data->getLine();
        if (line.length() > 0) {
            calc->input(line);
            line = calc->run();
            emit siReaded();
            if (base->insertRow(line)) {
                emit siWrited();
            } else {
                qDebug() << "Error of write";
                break;
            }
        } else {
            qDebug() << "Error of read. Readed line: " + line;
            break;
        }
        if (i%1000 == 0 && i != 0) {
            emit siTime();
        }
        QCoreApplication::processEvents();
    }
}

void Worker::slPause()
{
    run = false;
}

void Worker::slStop()
{
    slNeedBase(path);
    run = false;
    emit siReset();
}

void Worker::slDisconnecting()
{
    if (base->disconnect()) {
        qDebug() << "disconnected";
    }
}
