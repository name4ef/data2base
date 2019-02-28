#include "application.h"

Application::Application(int &argc, char **&argv, const QString filename) :
    QApplication(argc, argv),
    pConfig(0)
{
    QString configPath = QApplication::applicationDirPath()
            + QDir::separator() + filename;

    QFile file(configPath);
    if (!file.exists()) {
        qDebug() << "creating config file: " + configPath;
        if (!file.open(QIODevice::WriteOnly)) {
            qWarning() << "can't create config file: " + configPath;
        }
        QTextStream stream(&file);
        stream << "# type of dbms: pgsql, mysql" << endl
               << "type = pgsql" << endl
               << "hostname = localhost" << endl
               << "database = test1" << endl
               << "username = postgres" << endl
               << "password = toor" << endl
               << endl
               << "delay = 10" << endl;
        file.close();
        if (stream.status() != QTextStream::Ok) {
            qWarning() << "error of writing file";
        }
    }

    pConfig = new Config(configPath, QSettings::IniFormat);

}

Application *Application::App()
{
    return (Application*)qApp;
}

Config *Application::config()
{
    return pConfig;
}
