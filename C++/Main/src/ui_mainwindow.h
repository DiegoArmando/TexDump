/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *log_action;
    QAction *set_hot_key_action;
    QAction *copy_close_action;
    QWidget *centralWidget;
    QPushButton *send_button;
    QPushButton *log_button;
    QLabel *your_ip_lable;
    QPlainTextEdit *message_text_box;
    QLabel *destination_ip_lable;
    QComboBox *computer_list_box;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QMenu *menuSettings;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 291);
        log_action = new QAction(MainWindow);
        log_action->setObjectName(QStringLiteral("log_action"));
        log_action->setCheckable(true);
        log_action->setMenuRole(QAction::PreferencesRole);
        set_hot_key_action = new QAction(MainWindow);
        set_hot_key_action->setObjectName(QStringLiteral("set_hot_key_action"));
        set_hot_key_action->setMenuRole(QAction::PreferencesRole);
        copy_close_action = new QAction(MainWindow);
        copy_close_action->setObjectName(QStringLiteral("copy_close_action"));
        copy_close_action->setEnabled(true);
        copy_close_action->setMenuRole(QAction::PreferencesRole);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        send_button = new QPushButton(centralWidget);
        send_button->setObjectName(QStringLiteral("send_button"));
        send_button->setGeometry(QRect(310, 180, 75, 61));
        log_button = new QPushButton(centralWidget);
        log_button->setObjectName(QStringLiteral("log_button"));
        log_button->setGeometry(QRect(310, 100, 75, 61));
        your_ip_lable = new QLabel(centralWidget);
        your_ip_lable->setObjectName(QStringLiteral("your_ip_lable"));
        your_ip_lable->setGeometry(QRect(20, 9, 271, 21));
        message_text_box = new QPlainTextEdit(centralWidget);
        message_text_box->setObjectName(QStringLiteral("message_text_box"));
        message_text_box->setGeometry(QRect(30, 110, 261, 121));
        destination_ip_lable = new QLabel(centralWidget);
        destination_ip_lable->setObjectName(QStringLiteral("destination_ip_lable"));
        destination_ip_lable->setGeometry(QRect(20, 40, 101, 20));
        computer_list_box = new QComboBox(centralWidget);
        computer_list_box->setObjectName(QStringLiteral("computer_list_box"));
        computer_list_box->setGeometry(QRect(150, 40, 131, 22));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(310, 30, 75, 51));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuSettings->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TextDump", 0));
        log_action->setText(QApplication::translate("MainWindow", "Log", 0));
        set_hot_key_action->setText(QApplication::translate("MainWindow", "Set Hot Key", 0));
        copy_close_action->setText(QApplication::translate("MainWindow", "Set Copy Close Hot Key", 0));
        send_button->setText(QApplication::translate("MainWindow", "Send", 0));
        log_button->setText(QApplication::translate("MainWindow", "Log", 0));
        your_ip_lable->setText(QApplication::translate("MainWindow", "Your Computer Name: ", 0));
        destination_ip_lable->setText(QApplication::translate("MainWindow", "Send messages to :", 0));
        computer_list_box->clear();
        computer_list_box->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "A Computer", 0)
         << QApplication::translate("MainWindow", "Another Computer", 0)
        );
        pushButton->setText(QApplication::translate("MainWindow", "Log In", 0));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
