#ifndef DIALOG_H
#define DIALOG_H

#include <QDebug>
#include <QFileDialog>
#include <QDialog>
#include <QThread>

#include "ui_dialog.h"
#include "worker.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QString filePath;
    bool connected = false;
    bool selected = false;
    bool baseReady = false;
    int countOfRead;
    int countOfWrite;
    QThread *thread;
    Worker *worker;
    void checkForStart();

public slots:
    void setStatus(QString);
    void setConnected();
    void setReady();

private slots:
    void browse();
    void start();
    void upperWrite();
    void upperRead();

signals:
    void getFirstLine(QString);
    void getLine();
    void needBase(QString);
    void run();
};

#endif // DIALOG_H
