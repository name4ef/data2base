#include "database.h"
#include "application.h"

Database::Database()
{
    Config* conf = Application::theApp()->config();

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    qDebug() << conf->get("hostname");
    db.setHostName(conf->get("hostname"));
    db.setDatabaseName(conf->get("database"));
    db.setUserName(conf->get("username"));
    db.setPassword(conf->get("password"));
    if (!db.open()) {
        qDebug() << db.lastError();
    } else {
        qDebug() << "Success!";
    }
}
