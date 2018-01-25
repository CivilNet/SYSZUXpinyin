#ifndef OTHERDIALOG_H
#define OTHERDIALOG_H

#include <QDialog>

namespace Ui {
class OtherDialog;
}

class OtherDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit OtherDialog(QWidget *parent = 0);
    ~OtherDialog();

signals:
    void dialogSelect(int dlgno);
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::OtherDialog *ui;
};

#endif // OTHERDIALOG_H
