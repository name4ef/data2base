#ifndef DEVICE_H
#define DEVICE_H

#include <QThread>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

class Data : public QThread
{
    Q_OBJECT
public:
    void run();

private:
    QString path;
    QFile file;
    QTextStream stream;

public slots:
    void getFirstLine(QString);
    void getLine();

signals:
    void firstLine(QString);
    void line(QString);
    void fileEnded();
    void waitBase(QString, QStringList);
};

#endif // DEVICE_H
