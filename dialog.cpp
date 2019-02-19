#include "dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    filePath(""),
    countOfRead(0),
    countOfWrite(0)
{
    ui->setupUi(this);
    ui->status->setText("connecting to dbms...");
    ui->startButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    ui->stopButton->setDisabled(true);

    worker = new Worker();
    thread = new QThread(this);
    worker->moveToThread(thread);
    thread->start();

    connect(worker, SIGNAL(valueChange(int)), ui->lcdNumber, SLOT(display(int)));
    connect(worker, SIGNAL(finished()), this, SLOT(close()));
    connect(worker, SIGNAL(connected()), this, SLOT(setConnected()));
    connect(worker, SIGNAL(ready()), this, SLOT(setReady()));
    connect(worker, SIGNAL(readed()), this, SLOT(upperRead()));
    connect(worker, SIGNAL(writed()), this, SLOT(upperWrite()));

    connect(thread, SIGNAL(started()), worker, SLOT(slotDoWork()));
    connect(thread, SIGNAL(started()), worker, SLOT(slotMakeConnection()));

    connect(this, SIGNAL(needBase(QString)), worker, SLOT(slotPrepareBase(QString)));
    connect(this, SIGNAL(run()), worker, SLOT(slotRun()));

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browse()));
}

Dialog::~Dialog()
{
    thread->quit();
    thread->wait();
    delete worker;
    delete ui;
}

void Dialog::checkForStart()
{
    if (connected && selected && baseReady) {
        ui->startButton->setEnabled(true);
    } else if (connected && selected) {
        ui->status->setText("preparing database...");
        //emit getFirstLine(filePath);
        emit needBase(filePath);
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

void Dialog::start()
{
    emit run();
}

void Dialog::setStatus(QString str)
{
    ui->status->setText(str);
}

void Dialog::setConnected()
{
    connected = true;
    ui->status->setText("connected");
    checkForStart();
}

void Dialog::setReady()
{
    baseReady = true;
    checkForStart();
}

void Dialog::upperWrite()
{
    ui->writedValue->setNum(++countOfWrite);
}

void Dialog::upperRead()
{
    ui->readedValue->setNum(++countOfRead);
}
