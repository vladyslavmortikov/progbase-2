#include "xml_storage.hpp"

#include <QString>
#include <QDebug>
#include <QFile>
#include <QtXml>

using namespace std;

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

Topic domElementToTopic(QDomElement &element)
{
    Topic top;
    top.id = element.attribute("id").toInt();
    top.data = element.attribute("data").toStdString();
    top.topic = element.attribute("topic").toStdString();
    top.students = element.attribute("students").toInt();
    return top;
}

QDomElement topicToDomElement(QDomDocument &doc, Topic & top){

    QDomElement topic_el = doc.createElement("topics");
    topic_el.setAttribute("id", top.id);
    topic_el.setAttribute("title", top.data.c_str());
    topic_el.setAttribute("lectorer", top.topic.c_str());
    topic_el.setAttribute("students", top.students);

    return topic_el;
}

bool XmlStorage::open()
{
    string filename = this->dir_name_ + "/lections.xml";
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
    qDebug() << "OK!:)";

    QDomElement root = doc.documentElement();

    for(int i = 0; i < root.childNodes().size(); i++)
    {
        QDomNode node = root.childNodes().at(i);
        QDomElement element = node.toElement();
        Lection lec = domElementToLection(element);
        this->lections_.push_back(lec);
    }

    //----------------------------------------

    string topicFilename = this->dir_name_ + "/topics.xml";
    QString q_topicFilename = QString::fromStdString(topicFilename);
    QFile fileTF(q_topicFilename);

    bool isOpenedTF = fileTF.open(QFile::ReadOnly);
    if (!isOpenedTF){
        qDebug() << "CAN'T OPEN THE FILE " << q_topicFilename;
        return false;
    }

    QTextStream tstf(&fileTF);
    QString textTF = tstf.readAll();
    fileTF.close();

    QDomDocument docTF;
    QString errorMessageTF;
    int errorLineTF;
    int errorColumnTF;
    if (!docTF.setContent(textTF,&errorMessageTF,&errorLineTF,&errorColumnTF)){
        qDebug() << "Error parsing XML text: " << errorMessageTF;
        qDebug() << "at line" << errorLineTF << ", column " << errorColumnTF;
        return false;
    }
    qDebug() << "OK!:)";

    QDomElement rootTF = docTF.documentElement();

    for(int i = 0; i < rootTF.childNodes().size(); i++)
    {
        QDomNode nodeTF = rootTF.childNodes().at(i);
        QDomElement elementTF = nodeTF.toElement();
        Topic top = domElementToTopic(elementTF);
        this->topics_.push_back(top);
    }

    return true;
}

bool XmlStorage::close()
{
    QDomDocument doc;
    QDomElement root = doc.createElement("lections");

    for(Lection & lec : this->lections_){
       QDomElement lection_el = lectionToDomElement(doc, lec);
         root.appendChild(lection_el);
    }

    doc.appendChild(root);
    QString xml_text = doc.toString(4);

    string filename = this->dir_name_ + "/lections.xml";
    QString q_filename = QString::fromStdString(filename);
    QFile file(q_filename);

    bool isOpened = file.open(QFile::WriteOnly);
    if (!isOpened){
        qDebug() << "CAN'T OPEN THE FILE " << q_filename;
        return false;
    }

    QTextStream ts(&file);

    ts << xml_text;


    file.close();

    //--------------------------------------------
    QDomDocument docT;
    QDomElement rootT = docT.createElement("topics");

    for(Topic & top : this->topics_){
       QDomElement topic_el = topicToDomElement(doc, top);
         rootT.appendChild(topic_el);
    }

    docT.appendChild(rootT);
    QString xml_textT = doc.toString(4);

    string filenameT = this->dir_name_ + "/topics.xml";
    QString q_filenameT = QString::fromStdString(filenameT);
    QFile fileT(q_filenameT);

    bool isOpenedT = fileT.open(QFile::WriteOnly);
    if (!isOpenedT){
        qDebug() << "CAN'T OPEN THE FILE " << q_filenameT;
        return false;
    }

    QTextStream tsT(&file);

    tsT << xml_textT;


    file.close();

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

int XmlStorage::getNewTopicId()
{
    int max = 0;
    for (Topic top : this->topics_)
    {
        if (max < top.id)
            max = top.id;
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

vector<Topic> XmlStorage::getAllTopics()
{
    return this->topics_;
}

optional<Topic> XmlStorage::getTopicById(int lection_id)
{
    for (Topic &top : this->topics_)
    {
        if (top.id == lection_id)
        {
            return top;
        }
    }

    return nullopt;
}

bool XmlStorage::updateTopic(const Topic &topic)
{
    for (int i = 0; i < topics_.size(); i++)
    {
        if (topics_[i].id == topic.id)
        {
            topics_[i] = topic;
            return 1;
        }
    }
    return 0;
}

bool XmlStorage::removeTopic(int topic_id)
{
    for (int i = 0; i < topics_.size(); i++)
    {
        if (topics_[i].id == topic_id)
        {
            topics_.erase(topics_.begin() + i);
            return 1;
        }
    }
    return 0;
}

int XmlStorage::insertTopic(const Topic &topic)
{
    Topic top = topic;
    top.id = getNewTopicId();
    topics_.push_back(top);
    return top.id;
}

