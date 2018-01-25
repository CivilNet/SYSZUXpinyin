#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

#include "otherdialog.h"
#include "inputdialog.h"

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();


    
private slots:
    void selectDialog(int dialogTo);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainDialog *ui;
    OtherDialog *otherDialog;
    InputDialog *inputDialog;
};

#endif // MAINDIALOG_H
