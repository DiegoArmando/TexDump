#ifndef USERINFO_H
#define USERINFO_H

#include <QWidget>

namespace Ui {
class userinfo;
}

class userinfo : public QWidget
{
    Q_OBJECT

public:
    explicit userinfo(QWidget *parent = 0);
    ~userinfo();

private slots:
    void on_login_button_clicked();

    void on_register_button_clicked();

private:
    Ui::userinfo *ui;
};

#endif // USERINFO_H
