#include "data.h"

void Data::run()
{

}

void Data::getFirstLine(QString path)
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
        emit waitBase(name, line);
    } else {
        emit fileEnded();
    }
}

void Data::getLine()
{

}
