#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QDir>
#include "config.h"
#include <QDebug>

class Application : public QApplication
{
    Q_OBJECT
private:
    Config* pConfig;

public:
    Application(int& argc, char**& argv, const QString filename = "config.ini");

    static Application* theApp();

    Config* config();
};

#endif // APPLICATION_H
