#include "auth.h"
#include "ui_auth.h"

auth::auth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::auth)
{
    ui->setupUi(this);
}
std::vector<std::string> auth::getData(){
    std::vector<std::string> vec;
    vec.push_back(ui->lineEdit->text().toStdString());
    vec.push_back(ui->lineEdit_2->text().toStdString());
    return vec;
}
auth::~auth()
{
    delete ui;
}
