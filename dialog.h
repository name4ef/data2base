#ifndef DIALOG_H
#define DIALOG_H

#include <QDebug>
#include <QFileDialog>
#include <QDialog>
#include <QThread>
#include <QDateTime>
#include <QStack>

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
    bool connected;
    bool selected;
    bool baseReady;
    bool run;
    int countOfRead;
    int countOfWrite;
    int delay;
    QThread *thread;
    Worker *worker;
    qint64 lastTime;
    QStack<qint64> deltaTime;
    void checkForStart();
    unsigned int getDeltaTime(QStack<qint64>*);

private slots:
    void _slBrowse();
    void _slStart();
    void _slStop();
    void _slWrited();
    void _slReaded();
    void _slTime();
    void _slStatus(QString);
    void _slConnected();
    void _slReady();
    void _slReset();

signals:
    void siNeedBase(QString);
    void siStart();
    void siPause();
    void siStop();
    void siDisconnecting();
};

#endif // DIALOG_H
