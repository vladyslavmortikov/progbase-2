#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "lection.h"

namespace Ui {
class addDialog;
}

class addDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addDialog(Lection *lec,QWidget *parent = nullptr);
    ~addDialog();
    Lection data();

private:
    Ui::addDialog *ui;
};

#endif // ADDDIALOG_H
