#include "adddialog.h"
#include "ui_adddialog.h"

addDialog::addDialog(Lection *lec,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDialog)
{

    ui->setupUi(this);
    if(lec !=nullptr)
    {
        ui->lineEdit->setText(QString::fromStdString(lec->title));
        ui->lineEdit_2->setText(QString::fromStdString(lec->lectorer));
        ui->spinBox_2->setValue(lec->students);
    }
}

addDialog::~addDialog()
{
    delete ui;
}

Lection addDialog::data(){
    Lection lec;
    lec.title=ui->lineEdit->text().toStdString();
    lec.lectorer=ui->lineEdit_2->text().toStdString();
    lec.students=ui->spinBox_2->value();
    return lec;
}
