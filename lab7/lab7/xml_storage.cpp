#include "xml_storage.h"

#include <QString>
#include <QDebug>
#include <QFile>
#include <QtXml>

using namespace std;

//~XmlStorage(){

//}

Lection domElementToLection(QDomElement &element)
{
    Lection lec;
    lec.id = element.attribute("id").toInt();
    lec.title = element.attribute("title").toStdString();
    lec.lectorer = element.attribute("lectorer").toStdString();
    lec.students = element.attribute("students").toInt();
    return lec;
}

QDomElement lectionToDomElement(QDomDocument &doc, Lection & lec){

    QDomElement lection_el = doc.createElement("lections");
    lection_el.setAttribute("id", lec.id);
    lection_el.setAttribute("title", lec.title.c_str());
    lection_el.setAttribute("lectorer", lec.lectorer.c_str());
    lection_el.setAttribute("students", lec.students);

    return lection_el;
}

bool XmlStorage::load()
{
    string filename = this->dir_name_;
    QString q_filename = QString::fromStdString(filename);
    QFile file(q_filename);

    bool isOpened = file.open(QFile::ReadOnly);
    if (!isOpened){
        qDebug() << "CAN'T OPEN THE FILE " << q_filename;
        return false;
    }

    QTextStream ts(&file);
    QString text = ts.readAll();
    file.close();

    QDomDocument doc;
    QString errorMessage;
    int errorLine;
    int errorColumn;
    if (!doc.setContent(text,&errorMessage,&errorLine,&errorColumn)){
        qDebug() << "Error parsing XML text: " << errorMessage;
        qDebug() << "at line" << errorLine << ", column " << errorColumn;
        return false;
    }

    QDomElement root = doc.documentElement();

    for(int i = 0; i < root.childNodes().size(); i++)
    {
        QDomNode node = root.childNodes().at(i);
        QDomElement element = node.toElement();
        Lection lec = domElementToLection(element);
        this->lections_.push_back(lec);
    }

    return true;
}

bool XmlStorage::save(){

    QFile check(QString ::fromStdString(dir_name_));
    QFileInfo info(check);
    QDir dir(QString::fromStdString(dir_name_));

    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QDomDocument lec_doc;
    QDomElement lec_root=lec_doc.createElement("lections");
    lec_doc.appendChild(lec_root);
    for(Lection lec : lections_){
        lec_root.appendChild(lectionToDomElement(lec_doc,lec));
    }
    string filename;
    QString lec_xml_text=lec_doc.toString(4);
    if (info.isDir()){
        filename=dir_name_+"lections.xml";
        qDebug()<<"it dir, new path="<<QString::fromStdString(filename);
    }
    if (info.isFile())
        filename=dir_name_;
    QString q_filename= QString::fromStdString(filename);
    QFile lec_file(q_filename);
    if(!lec_file.open(QFile::WriteOnly)){
        qDebug()<<"file not opened";
        return 0;
    }
    QTextStream ts1(&lec_file);
    ts1 << lec_xml_text;
    lec_file.close();

    return true;
}

int XmlStorage::getNewLectionId()
{
    int max = 0;
    for (Lection lec : this->lections_)
    {
        if (max < lec.id)
            max = lec.id;
    }
    return max + 1;
}

vector<Lection> XmlStorage::getAllLections()
{
    return this->lections_;
}

optional<Lection> XmlStorage::getLectionById(int lection_id)
{
    for (Lection &lec : this->lections_)
    {
        if (lec.id == lection_id)
        {
            return lec;
        }
    }

    return nullopt;
}

bool XmlStorage::updateLection(const Lection &lection)
{
    for (int i = 0; i < lections_.size(); i++)
    {
        if (lections_[i].id == lection.id)
        {
            lections_[i] = lection;
            return 1;
        }
    }
    return 0;
}

bool XmlStorage::removeLection(int lection_id)
{
    for (int i = 0; i < lections_.size(); i++)
    {
        if (lections_[i].id == lection_id)
        {
            lections_.erase(lections_.begin() + i);
            return 1;
        }
    }
    return 0;
}

int XmlStorage::insertLection(const Lection &lection)
{
    Lection lec = lection;
    lec.id = getNewLectionId();
    lections_.push_back(lec);
    return lec.id;
}
