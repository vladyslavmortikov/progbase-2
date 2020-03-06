#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QFileDialog>
#include "xml_storage.h"
#include <QMessageBox>
#include "adddialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionNew_Storage,&QAction::triggered,this,&MainWindow::onNew);
    connect(ui->actionOpen_storage,&QAction::triggered,this,&MainWindow::onOpen);
    setDefault();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNew(){
    if(storage_!=nullptr)
        delete(XmlStorage*)storage_;
    storage_=nullptr;
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString current_dir = QDir::currentPath();
    QString default_name = "new_storage";
    QString folder_path = dialog.getSaveFileName(
        this,
        "Select New Storage Folder",
        current_dir + "/" + default_name,
        "Folders");
    folder_path+="/";
    storage_ = new XmlStorage(folder_path.toStdString());
    storage_->save();
    ui->pushButton->setEnabled(true);
}

void MainWindow::onOpen(){
    if(storage_!=nullptr)
        delete(XmlStorage*)storage_;
    storage_=nullptr;
    QString fileName = QFileDialog::getOpenFileName(
        this,              // parent
        "Dialog Caption",  // caption
        "",                // directory to start with
        "XML (*.xml);;All Files (*)");  // file name filter
    qDebug() << fileName;
    storage_ = new XmlStorage(fileName.toStdString());
    storage_->load();
    fillList();
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_pushButton_clicked()
{
    addDialog addialog_(nullptr,this);
    addialog_.setWindowTitle("Creating New Course of Lections");
    int status=addialog_.exec();
    if (status)
    {
        storage_->insertLection(addialog_.data());
        storage_->save();
    }
    fillList();
}
void MainWindow::fillList(){
    ui->listWidget->clear();
    for (Lection lec : storage_->getAllLections()){
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
    Lection lec = var.value<Lection>();
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
        storage_->save();
        fillList();
        setDefault();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QList <QListWidgetItem *>items=ui->listWidget->selectedItems();
    QListWidgetItem * selectedItem=items.at(0);
    QVariant var = selectedItem->data(Qt::UserRole);
    Lection lec =var.value<Lection>();
    addDialog addialog_(&lec,this);
    addialog_.setWindowTitle("Edition Course Of Lection");
    int status=addialog_.exec();
    if (status){
        Lection changed=addialog_.data();
        changed.id=lec.id;
        storage_->updateLection(changed);
        storage_->save();
        fillList();
    }
    disableEditing();
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
