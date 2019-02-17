#include "dialog.h"
#include "ui_dialog.h"
#include "database.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QObject::connect(ui->startButton, SIGNAL(clicked()), this, SLOT(connectToDb()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::connectToDb()
{
    Database db;
}
