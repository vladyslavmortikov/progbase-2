#include "csv_storage.hpp"

using namespace std;

void writeAllToFile(string const &filename, string const &text);

bool CsvStorage::open()
{
    string lections_filename = this->dir_name_ + "/lections.csv";

    ifstream file;

    file.open(lections_filename, ios::in);

    if (!file.good())
    {
        cerr << "Can't open the file: " << lections_filename << endl;
        abort();
    }

    string tmp, str;
    while (getline(file, tmp))
    {
        str += tmp + '\n';
        tmp.clear();
    }

    CsvTable lections_table = Csv::createTableFromString(str);

    for (CsvRow &row : lections_table)
    {
        Lection lec;
        if (row.size() > 0)
            lec.id = stoi(row[0]);
        if (row.size() > 1)
            lec.title = row[1];
        if (row.size() > 2)
            lec.lectorer = row[2];
        if (row.size() > 3)
            lec.students = stoi(row[3]);
        this->lections_.push_back(lec);
    }
    file.close();

    // ----------------------------------

    string topics_filename = this->dir_name_ + "/topics.csv";

    file.open(topics_filename, ios::in);

    if (!file.good())
    {
        cerr << "Can't open the file: " << topics_filename << endl;
        abort();
    }

    str.clear();

    while (getline(file, tmp))
    {
        str += tmp + '\n';
        tmp.clear();
    }

    CsvTable topic_table = Csv::createTableFromString(str);

    for (CsvRow &row : topic_table)
    {
        Topic top;
        if (row.size() > 0)
            top.id = stoi(row[0]);
        if (row.size() > 1)
            top.data = row[1];
        if (row.size() > 2)
            top.topic = row[2];
        if (row.size() > 3)
            top.students = stoi(row[3]);
        this->topics_.push_back(top);
    }
    file.close();

    return true;
}

bool CsvStorage::close()
{
    CsvTable table;

    for (Lection lec : lections_)
    {
        CsvRow row;
        row.push_back(to_string(lec.id));
        row.push_back(lec.title);
        row.push_back(lec.lectorer);
        row.push_back(to_string(lec.students));
        table.push_back(row);
    };

    string filename = "lections.csv";
    ofstream output;
    output.open(dir_name_ + filename);
    if (!output.is_open())
    {
        cout << "no such file: " << dir_name_;
        output.close();
        return 0;
    }
    output << Csv::createStringFromTable(table);
    output.close();

    ////////////////

    CsvTable table1;

    for (Topic top : topics_)
    {

        CsvRow row;
        row.push_back(to_string(top.id));
        row.push_back(top.data);
        row.push_back(top.topic);
        row.push_back(to_string(top.students));
        table1.push_back(row);
    }

    filename = "topics.csv";
    output.open(dir_name_ + filename);

    if (!output.is_open())
    {
        cout << "no such file: " << dir_name_;
        output.close();
        return 0;
    }

    output << Csv::createStringFromTable(table1);
    output.close();
    return 1;
}

int CsvStorage::getNewLectionId()
{
    int max = 0;
    for (Lection lec : this->lections_)
    {
        if (max < lec.id)
            max = lec.id;
    }
    return max + 1;
}

int CsvStorage::getNewTopicId()
{
    int max = 0;
    for (Topic top : this->topics_)
    {
        if (max < top.id)
            max = top.id;
    }
    return max + 1;
}

vector<Lection> CsvStorage::getAllLections()
{
    return this->lections_;
}

optional<Lection> CsvStorage::getLectionById(int lection_id)
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
bool CsvStorage::updateLection(const Lection &lection)
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

bool CsvStorage::removeLection(int lection_id)
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

int CsvStorage::insertLection(const Lection &lection)
{
    Lection lec = lection;
    lec.id = getNewLectionId();
    lections_.push_back(lec);
    return lec.id;
}

vector<Topic> CsvStorage::getAllTopics()
{
    return this->topics_;
}

optional<Topic> CsvStorage::getTopicById(int lection_id)
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

bool CsvStorage::updateTopic(const Topic &topic)
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

bool CsvStorage::removeTopic(int topic_id)
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

int CsvStorage::insertTopic(const Topic &topic)
{
    Topic top = topic;
    top.id = getNewTopicId();
    topics_.push_back(top);
    return top.id;
}

void writeAllToFile(string const &filename, string const &text)
{
    ofstream file;
    file.open(filename);
    if (!file.good())
    {
        cerr << "The file cannot open for write: " << filename << endl;
        abort();
    }

    file << text;
    file.close();
}
