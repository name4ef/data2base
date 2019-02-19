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

private:
   QSqlDatabase db;
   QString table;
};

#endif // DATABASE_H
