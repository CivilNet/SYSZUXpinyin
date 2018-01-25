#include "maindialog.h"
#include "ui_maindialog.h"
#include "inputdialog.h"
#include "ui_inputdialog.h"
#include "otherdialog.h"
#include "ui_otherdialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//delete title and border

    //define the dialog used
    otherDialog = new OtherDialog;
    inputDialog = new InputDialog;

    //connect the signals select dialog
    connect(otherDialog, SIGNAL(dialogSelect(int)), this, SLOT(selectDialog(int)));
    connect(inputDialog, SIGNAL(dialogSelect(int)), this, SLOT(selectDialog(int)));
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::selectDialog(int dialogTo)
{
    switch(dialogTo)
    {
    case 1:
         MainDialog::show();
         MainDialog::raise();
         break;
    case 2:
        otherDialog->show();
        otherDialog->raise();
        break;
    case 3:
        inputDialog->show();
        inputDialog->raise();
        break;
    default:
        break;
    }
}

void MainDialog::on_pushButton_clicked()
{
    selectDialog(3);
}

void MainDialog::on_pushButton_2_clicked()
{
    selectDialog(2);
}
