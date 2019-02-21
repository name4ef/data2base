#include "dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    filePath(""),
    connected(false),
    selected(false),
    baseReady(false),
    run(false),
    countOfRead(0),
    countOfWrite(0),
    thread(new QThread(this)),
    worker(new Worker),
    lastTime(0)
{
    ui->setupUi(this);
    ui->startPauseButton->setDisabled(true);
    ui->stopButton->setDisabled(true);

    connect(worker, SIGNAL(siConnected()), this, SLOT(_slConnected()));
    connect(worker, SIGNAL(siReady()), this, SLOT(_slReady()));
    connect(worker, SIGNAL(siReaded()), this, SLOT(_slReaded()));
    connect(worker, SIGNAL(siWrited()), this, SLOT(_slWrited()));
    connect(worker, SIGNAL(siStatus(QString)), this, SLOT(_slStatus(QString)));
    connect(worker, SIGNAL(siTime()), this, SLOT(_slTime()));
    connect(worker, SIGNAL(siReset()), this, SLOT(_slReset()));

    connect(thread, SIGNAL(started()), worker, SLOT(slMakeConnection()));

    connect(this, SIGNAL(siNeedBase(QString)), worker, SLOT(slNeedBase(QString)));
    connect(this, SIGNAL(siStart()), worker, SLOT(slStart()));
    connect(this, SIGNAL(siPause()), worker, SLOT(slPause()));
    connect(this, SIGNAL(siStop()), worker, SLOT(slStop()));

    connect(ui->startPauseButton, SIGNAL(clicked()), this, SLOT(_slStart()));
    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(_slBrowse()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(_slStop()));

    worker->moveToThread(thread);
    thread->start();

    Config* conf = Application::App()->config();
    delay = conf->get("delay").toInt();
}

Dialog::~Dialog()
{
    emit siStop();
    thread->quit();
    qDebug() << "waiting thread";
    thread->wait();
    qDebug() << "thread finished";
}

void Dialog::checkForStart()
{
    if (connected && selected && baseReady) {
        ui->startPauseButton->setEnabled(true);
    } else if (connected && selected) {
        emit siNeedBase(filePath);
    }
}

unsigned int Dialog::getDeltaTime(QStack<qint64> *s)
{
    int max = 100;
    if (s->size() > max) {
        s->resize(max);
    }
    qint64 all = 0;
    for (int i = 0; i < s->size(); ++i) {
        all += s->at(i);
    }
    return all/s->size();
}

void Dialog::_slBrowse()
{
    baseReady = false;
    ui->startPauseButton->setDisabled(true);
    QString fn = QFileDialog::getOpenFileName(this);
    if (fn != "") {
        filePath = fn;
        ui->pathToFile->setText(filePath);
        selected = true;
        checkForStart();
    }
}

void Dialog::_slStart()
{
    if (run) {
        run = false;
        ui->startPauseButton->setText("start");
        emit siPause();
    } else {
        run = true;
        ui->startPauseButton->setText("pause");
        emit siStart();
    }
    ui->browseButton->setDisabled(true);
    ui->stopButton->setEnabled(true);
}

void Dialog::_slStop()
{
    run = false;
    ui->startPauseButton->setText("start");
    ui->stopButton->setDisabled(true);
    ui->browseButton->setEnabled(true);
    emit siStop();
}

void Dialog::_slStatus(QString str)
{
    ui->status->setText(str);
}

void Dialog::_slConnected()
{
    connected = true;
    ui->status->setText("connected");
    checkForStart();
}

void Dialog::_slReady()
{
    baseReady = true;
    checkForStart();
}

void Dialog::_slReset()
{
    countOfRead = 0;
    countOfWrite = 0;
    ui->readedValue->setNum(0);
    ui->writedValue->setNum(0);
    ui->momentTimeValue->setNum(0);
}

void Dialog::_slWrited()
{
    ui->writedValue->setNum(++countOfWrite);
}

void Dialog::_slReaded()
{
    ui->readedValue->setNum(++countOfRead);
}

void Dialog::_slTime()
{
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    qint64 current = now - lastTime - delay*1000;
    lastTime = now;
    deltaTime.prepend(current);
    qint64 delta = getDeltaTime(&deltaTime);

    ui->momentTimeValue->setNum((int)current);
    ui->deltaTimeValue->setText(QString::number(delta));
}
