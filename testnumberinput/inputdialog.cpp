#include "inputdialog.h"
#include "ui_inputdialog.h"

#include "syszuxim.h"
#include "syszuxpinyin.h"

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//delete title and border

    QWSInputMethod* im = new SyszuxIM;
    QWSServer::setCurrentInputMethod(im);
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::on_pushButton_clicked()
{
    emit dialogSelect(1);
}

void InputDialog::on_pushButton_2_clicked()
{
    emit dialogSelect(2);
}
