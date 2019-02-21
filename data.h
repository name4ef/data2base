#ifndef DEVICE_H
#define DEVICE_H

#include <QThread>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>

#include "application.h"

class Data : public QObject
{
    Q_OBJECT
public:
    Data(QString);
    QString getFileName();
    QString getFirstLine();
    QString getLine();

private:
    QString path;
    QFile file;
    QTextStream stream;
    int delay;

signals:
    void firstLine(QString);
    void line(QString);
    void fileEnded();
    void waitBase(QString, QStringList);
};

#endif // DEVICE_H
