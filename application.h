#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QDir>
#include <QDebug>
#include "config.h"

class Application : public QApplication
{
    Q_OBJECT
private:
    Config* pConfig;

public:
    Application(int& argc, char**& argv, const QString filename = "config.ini");

    static Application* App();

    Config* config();
};

#endif // APPLICATION_H
