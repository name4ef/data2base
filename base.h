#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QLatin1String>

#include "application.h"

class Base : QObject
{
    Q_OBJECT
public:
    explicit Base(QObject *parent = nullptr) :
        QObject(parent)
    {}
    bool connect();
    bool prepareBase(QString, QStringList);
    bool insertRow(QString);
    bool disconnect();

private:
   QSqlDatabase db;
   QString table;
   QString f; // float definition for different dbms
   QString q; // quotes of header for different dbms
};

#endif // DATABASE_H
