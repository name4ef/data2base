#include "base.h"

void Base::run()
{
    Config* conf = Application::App()->config();

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(conf->get("hostname"));
    db.setDatabaseName(conf->get("database"));
    db.setUserName(conf->get("username"));
    db.setPassword(conf->get("password"));
    if (!db.open()) {
        qDebug() << db.lastError();
        status("can't connect to dbms");
    } else {
        status("connected to dbms");
        connected();
    }
}

void Base::prepareBase(QString name, QStringList headers)
{
    if (db.open()) {
        QSqlQuery query;
        QString str;
        name = name.toLower();

        if (db.tables().contains(name)) {
            qDebug() << "table exists";
            str = "DROP TABLE " + name;
            if (query.exec(str)) {
                qDebug() << "table removed";
            } else {
                qDebug() << query.lastError();
                qDebug() << db.lastError();
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

        str = "CREATE TABLE " + name + " " + schema + ";";
        if (query.exec(str)) {
            qDebug() << "table created";
            emit status("ready");
            emit ready();
        }
    }
}
