#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QFileDialog>
#include "sqlite_storage.h"
#include <QMessageBox>
#include "adddialog.h"
#include "auth.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen_storage,&QAction::triggered,this,&MainWindow::onOpen);
    setDefault();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpen(){
    if(storage_!=nullptr)
        delete(SQLiteStorage*)storage_;
    storage_=nullptr;

    QFileDialog dialog(this);
   dialog.setFileMode(QFileDialog::Directory);
   QString current_dir = QDir::currentPath();
   QString folder_path = dialog.getExistingDirectory(
       this,
       "Select Storage Folder",
       current_dir + "/../../../../lab9/data/sql",
       QFileDialog::ShowDirsOnly);
    if (folder_path.isNull())
        return;
    ifstream file;
       file.open(folder_path.toStdString()+"/data.sqlite");
       if(!file)
           return ;
    storage_ = new SQLiteStorage(folder_path.toStdString());
    if(storage_ -> open()){
        authfunc();
        ui->pushButton->setEnabled(true);
    }
}

void MainWindow::on_pushButton_clicked()
{
    addDialog addialog_(storage_,this);
    addialog_.setWindowTitle("creating new entity");
    int status=addialog_.exec();
    fillListWithUserId(storage_->getUser().user_id);
}

void MainWindow::fillListWithUserId(int user_id){
    ui->listWidget->clear();
    for (Lection lec : storage_->getUserLections(user_id)){
        QVariant qVariant;
        qVariant.setValue(lec);
        QListWidgetItem *qLectionListItem = new QListWidgetItem();
        qLectionListItem->setText(QString::fromStdString(lec.title));
        qLectionListItem->setData(Qt::UserRole, qVariant);
        ui->listWidget->addItem(qLectionListItem);
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QVariant var = item->data(Qt::UserRole);
    Lection lec =var.value<Lection>();
    ui->label_2->setText(QString::fromStdString(lec.title));
    ui->label_4->setText(QString::fromStdString(lec.lectorer));
    ui->label_6->setText(QString::number(lec.students));
    enableEditing();
}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton reply;
       reply = QMessageBox::question(
           this,
           "On delete",
           "Are you sure?",
           QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QList <QListWidgetItem *>items=ui->listWidget->selectedItems();
        QListWidgetItem * selectedItem=items.at(0);
        QVariant var = selectedItem->data(Qt::UserRole);
        Lection lec =var.value<Lection>();
        storage_->removeLection(lec.id);
        fillListWithUserId(storage_->getUser().user_id);
        setDefault();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QList <QListWidgetItem *>items=ui->listWidget->selectedItems();
    QListWidgetItem * selectedItem=items.at(0);
    QVariant var = selectedItem->data(Qt::UserRole);
   Lection lec =var.value<Lection>();
    addDialog addialog_(storage_,lec.id,this);
    addialog_.setWindowTitle("editing entity");
    addialog_.exec();

    disableEditing();

    fillListWithUserId(storage_->getUser().user_id);
}

void MainWindow::setDefault(){
    if (storage_==nullptr){
        disableEditing();
    }
        else{
            ui->pushButton->setEnabled(true );
            QList <QListWidgetItem *>items=ui->listWidget->selectedItems();
            if (items.size()<1){
                disableEditing();
            }
        }

}

void MainWindow::authfunc(){
    auth authdialog(this);
    User user;
    authdialog.setWindowTitle("logging in");
    while(true){
        if(authdialog.exec()){
            string login = authdialog.getData().at(0);
            string password = authdialog.getData().at(1);
            if (storage_->getUserAuth(login,password)) {
                storage_->setUser(*(storage_->getUserAuth(login,password)));
                break;
            } else
                authdialog.setWindowTitle("try one more time");
        }else {
            exit(0);
        }
    }
    fillListWithUserId(storage_->getUser().user_id);
}

void MainWindow::disableEditing(){
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
}
void MainWindow::enableEditing(){
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->label->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label_7->setVisible(true);
}
