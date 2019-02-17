#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>

class Config : public QSettings
{
public:
    Config(QString& path, Format format) :
        QSettings(path, format)
    {}

    QString get(QString);

};

#endif // CONFIG_H
