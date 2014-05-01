/********************************************************************************
** Form generated from reading UI file 'userinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINFO_H
#define UI_USERINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_userinfo
{
public:
    QLabel *label;
    QPushButton *login_button;
    QPushButton *register_button;
    QLineEdit *username_field;
    QLineEdit *password_feild;
    QLabel *label_2;
    QLineEdit *email_feild;
    QLabel *label_3;
    QLineEdit *computer_feild;
    QLabel *label_4;

    void setupUi(QWidget *userinfo)
    {
        if (userinfo->objectName().isEmpty())
            userinfo->setObjectName(QStringLiteral("userinfo"));
        userinfo->resize(291, 264);
        label = new QLabel(userinfo);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 46, 13));
        login_button = new QPushButton(userinfo);
        login_button->setObjectName(QStringLiteral("login_button"));
        login_button->setGeometry(QRect(30, 220, 75, 23));
        register_button = new QPushButton(userinfo);
        register_button->setObjectName(QStringLiteral("register_button"));
        register_button->setGeometry(QRect(170, 220, 75, 23));
        username_field = new QLineEdit(userinfo);
        username_field->setObjectName(QStringLiteral("username_field"));
        username_field->setGeometry(QRect(30, 40, 231, 20));
        password_feild = new QLineEdit(userinfo);
        password_feild->setObjectName(QStringLiteral("password_feild"));
        password_feild->setGeometry(QRect(30, 80, 231, 20));
        label_2 = new QLabel(userinfo);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 60, 46, 13));
        email_feild = new QLineEdit(userinfo);
        email_feild->setObjectName(QStringLiteral("email_feild"));
        email_feild->setGeometry(QRect(30, 130, 231, 20));
        label_3 = new QLabel(userinfo);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 110, 121, 16));
        computer_feild = new QLineEdit(userinfo);
        computer_feild->setObjectName(QStringLiteral("computer_feild"));
        computer_feild->setGeometry(QRect(30, 180, 231, 20));
        label_4 = new QLabel(userinfo);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 160, 46, 13));

        retranslateUi(userinfo);

        QMetaObject::connectSlotsByName(userinfo);
    } // setupUi

    void retranslateUi(QWidget *userinfo)
    {
        userinfo->setWindowTitle(QApplication::translate("userinfo", "Form", 0));
        label->setText(QApplication::translate("userinfo", "Username", 0));
        login_button->setText(QApplication::translate("userinfo", "Login", 0));
        register_button->setText(QApplication::translate("userinfo", "Register", 0));
        label_2->setText(QApplication::translate("userinfo", "Password", 0));
        label_3->setText(QApplication::translate("userinfo", "Email, not Rquired", 0));
        label_4->setText(QApplication::translate("userinfo", "Computer a name:", 0));
    } // retranslateUi

};

namespace Ui {
    class userinfo: public Ui_userinfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINFO_H
