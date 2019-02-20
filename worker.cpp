#include "worker.h"

Worker::Worker(QObject *parent) :
    QObject(parent)
{}

Worker::~Worker()
{
    delete data;
    delete base;
    delete calc;
}

void Worker::slotMakeConnection()
{
    base = new Base();
    emit status("connecting to dbms...");
    if (base->connect()) {
        emit connected();
    } else {
        emit status("can't connect to dbms");
    }
}

void Worker::slotPrepareBase(QString path)
{
    data = new Data(path);
    QString header = data->getFirstLine();
    QStringList headers = header.split(",");
    calc = new Calculator(headers.count());
    headers.append("Calc_zond1");
    headers.append("Calc_zond2");
    bool prepared = base->prepareBase(data->getFileName(), headers);
    if (prepared) {
        emit ready();
    }
}

void Worker::slotRun()
{
    for (int i; i < 100; ++i) {
        QString line = data->getLine();
        calc->input(line);
        line = calc->run();
        if (line.length() > 0) {
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
