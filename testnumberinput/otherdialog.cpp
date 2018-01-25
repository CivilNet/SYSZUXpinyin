#include "otherdialog.h"
#include "ui_otherdialog.h"

OtherDialog::OtherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OtherDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//delete title and border
}

OtherDialog::~OtherDialog()
{
    delete ui;
}

void OtherDialog::on_pushButton_clicked()
{
    emit dialogSelect(1);
}

void OtherDialog::on_pushButton_2_clicked()
{
    emit dialogSelect(3);
}
