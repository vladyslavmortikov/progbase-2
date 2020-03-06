#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <vector>
#include <QDialog>

namespace Ui {
class auth;
}

class auth : public QDialog
{
    Q_OBJECT

public:
    explicit auth(QWidget *parent = nullptr);
    std::vector<std::string> getData();
    ~auth();

private:
    Ui::auth *ui;
};

#endif // AUTH_H
