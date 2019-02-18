#ifndef DIALOG_H
#define DIALOG_H

#include <QDebug>
#include <QFileDialog>
#include <QDialog>
#include "ui_dialog.h"
#include "base.h"

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
    bool ready = false;
    void checkForStart();

public slots:
    void setStatus(QString);
    void setConnected();
    void setReady();

private slots:
    void start();
    void browse();

signals:
    void getFirstLine(QString);
};

#endif // DIALOG_H
