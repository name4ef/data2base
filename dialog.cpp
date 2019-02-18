#include "dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    filePath("")
{
    ui->setupUi(this);
    ui->status->setText("connecting to dbms...");
    ui->startButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    ui->stopButton->setDisabled(true);

    QObject::connect(ui->startButton, SIGNAL(clicked()), this, SLOT(start()));
    QObject::connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browse()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::checkForStart()
{
    if (connected && selected && ready) {
        ui->startButton->setEnabled(true);
    } else if (connected && selected) {
        ui->status->setText("preparing database...");
        emit getFirstLine(filePath);
    }
}

void Dialog::start()
{
    qDebug() << "clicked to start button...";
    if (filePath != "") {
        qDebug() << "selected file: " + filePath;
        QFile file(filePath);
        if (file.exists()) {
            if (!file.open(QIODevice::ReadOnly)) {
                qWarning() << "can't read file: " + filePath;
            }
            QTextStream stream(&file);
            for (int i = 0; i < 10; ++i) {
                if (!stream.atEnd()) {
                    qDebug() << stream.readLine();
                }
            }
            file.close();
            if (stream.status() != QTextStream::Ok) {
                qWarning() << "error of reading file";
            }
        }
    }
}

void Dialog::browse()
{
    QString fn = QFileDialog::getOpenFileName(this);
    if (fn != "") {
        filePath = fn;
        ui->pathToFile->setText(filePath);
        selected = true;
        checkForStart();
    }
}

void Dialog::setStatus(QString str)
{
    ui->status->setText(str);
}

void Dialog::setConnected()
{
    connected = true;
    checkForStart();
}

void Dialog::setReady()
{
    ready = true;
    checkForStart();
}
