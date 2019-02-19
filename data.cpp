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

QStringList Data::getFirstLine()
{
    if (file.isOpen()) {
        file.close();
    }

    file.setFileName(path);
    file.open(QIODevice::ReadOnly);
    stream.setDevice(&file);

    if (!stream.atEnd()) {
        QString name = QFileInfo(path).baseName();
        QStringList line = stream.readLine().split(",");
        line.append("Calc_zond1");
        line.append("Calc_zond2");
        return line;
    }
}


QString Data::getLine()
{
    if (!stream.atEnd()) {
        QThread::usleep(delay);
        return stream.readLine();
    }
}
