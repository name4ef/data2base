#include "base.h"

bool Base::connect()
{
    Config* conf = Application::App()->config();

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(conf->get("hostname"));
    db.setDatabaseName(conf->get("database"));
    db.setUserName(conf->get("username"));
    db.setPassword(conf->get("password"));
    if (!db.open()) {
        qDebug() << db.lastError();
        return false;
    } else {
        return true;
    }
}

bool Base::insertRow(QString values)
{
    if (db.isOpen()) {
        QSqlQuery query;
        QString str = "INSERT INTO " + table  + " VALUES (" + values + ");";
        if (query.exec(str)) {
            return true;
        } else {
            qDebug() << query.lastError();
            qDebug() << db.lastError();
            return false;
        }
    }
}

bool Base::prepareBase(QString name, QStringList headers)
{
    if (db.open()) {
        QSqlQuery query;
        QString str;
        table = name.toLower();

        if (db.tables().contains(table)) {
            qDebug() << "table exists";
            str = "DROP TABLE " + table;
            qDebug() << str;
            if (query.exec(str)) {
                qDebug() << "table removed";
            } else {
                qDebug() << query.lastError();
                qDebug() << db.lastError();
                return false;
            }
        }

        QString schema = "(";
        for(int i = 0; i < headers.count(); i++) {
           schema += headers[i] + " FLOAT";
           if (i != headers.count()-1) {
               schema += ", ";
           }
        }
        schema += ")";

        str = "CREATE TABLE " + table + " " + schema + ";";
        if (query.exec(str)) {
            qDebug() << "table created";
            return true;
        }
    }
}