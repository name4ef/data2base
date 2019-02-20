#include "data.h"

Data::Data(QString filepath)
{
    Config* conf = Application::App()->config();
    delay = conf->get("delay").toInt();
    path = filepath;
}

Data::~Data()
{
    if (file.isOpen()) {
        file.close();
    }
}

QString Data::getFileName()
{
    return QFileInfo(path).baseName();
}

QString Data::getFirstLine()
{
    if (file.isOpen()) {
        file.close();
    }

    file.setFileName(path);
    file.open(QIODevice::ReadOnly);
    stream.setDevice(&file);

    QString s;
    if (!stream.atEnd()) {
        s = stream.readLine();
    }
    return s;
}


QString Data::getLine()
{
    if (!stream.atEnd()) {
        QThread::usleep(delay);
        return stream.readLine();
    } else {
        return "";
    }
}
