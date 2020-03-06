#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include<QDebug>
#include <QDialog>
#include "storage.h"
#include <QListWidget>

namespace Ui {
class addDialog;
}

class addDialog : public QDialog
{
    Q_OBJECT
    Storage* storage_;
    int lection_id;
    int* lec_id=nullptr;
public:
    explicit addDialog(Storage* storage_,int cap_id,QWidget *parent = nullptr);
    explicit addDialog(Storage* storage_,QWidget *parent = nullptr);
    ~addDialog();
    void fillListsForNewMainEntity();
    void fillListsForEditedMainEntity(int lec_id);
    Lection data();

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::addDialog *ui;
};

#endif // ADDDIALOG_H
