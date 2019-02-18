#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QThread>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QLatin1String>
#include "application.h"

class Base : public QThread
{
    Q_OBJECT
public:
    void run();

private:
   QSqlDatabase db;

public slots:
    void prepareBase(QString, QStringList);

signals:
    void status(QString);
    void connected();
    void ready();
};

#endif // DATABASE_H
