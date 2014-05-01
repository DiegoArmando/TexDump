/********************************************************************************
** Form generated from reading UI file 'multi_message_box.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTI_MESSAGE_BOX_H
#define UI_MULTI_MESSAGE_BOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_multi_message_box
{
public:
    QLabel *num_messages_lable;
    QLabel *last_message_lable;
    QLabel *sender_timestamp_lable;
    QTextBrowser *message_text_box;
    QPushButton *close_button;
    QPushButton *copy_button;
    QPushButton *log_button;

    void setupUi(QWidget *multi_message_box)
    {
        if (multi_message_box->objectName().isEmpty())
            multi_message_box->setObjectName(QStringLiteral("multi_message_box"));
        multi_message_box->resize(391, 309);
        num_messages_lable = new QLabel(multi_message_box);
        num_messages_lable->setObjectName(QStringLiteral("num_messages_lable"));
        num_messages_lable->setGeometry(QRect(100, 10, 201, 16));
        last_message_lable = new QLabel(multi_message_box);
        last_message_lable->setObjectName(QStringLiteral("last_message_lable"));
        last_message_lable->setGeometry(QRect(10, 40, 71, 16));
        sender_timestamp_lable = new QLabel(multi_message_box);
        sender_timestamp_lable->setObjectName(QStringLiteral("sender_timestamp_lable"));
        sender_timestamp_lable->setGeometry(QRect(100, 35, 271, 21));
        message_text_box = new QTextBrowser(multi_message_box);
        message_text_box->setObjectName(QStringLiteral("message_text_box"));
        message_text_box->setGeometry(QRect(20, 60, 351, 171));
        close_button = new QPushButton(multi_message_box);
        close_button->setObjectName(QStringLiteral("close_button"));
        close_button->setGeometry(QRect(20, 240, 71, 51));
        copy_button = new QPushButton(multi_message_box);
        copy_button->setObjectName(QStringLiteral("copy_button"));
        copy_button->setGeometry(QRect(140, 240, 75, 51));
        log_button = new QPushButton(multi_message_box);
        log_button->setObjectName(QStringLiteral("log_button"));
        log_button->setGeometry(QRect(280, 240, 75, 51));

        retranslateUi(multi_message_box);

        QMetaObject::connectSlotsByName(multi_message_box);
    } // setupUi

    void retranslateUi(QWidget *multi_message_box)
    {
        multi_message_box->setWindowTitle(QApplication::translate("multi_message_box", "TextDump", 0));
        num_messages_lable->setText(QApplication::translate("multi_message_box", "You have recived NUMBER messages", 0));
        last_message_lable->setText(QApplication::translate("multi_message_box", "Last Message:", 0));
        sender_timestamp_lable->setText(QApplication::translate("multi_message_box", "From PERSON at Time", 0));
        message_text_box->setHtml(QApplication::translate("multi_message_box", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Text Text Text Text Text Text Text Text Text Text Text Text Text Text Text Text.</span></p></body></html>", 0));
        close_button->setText(QApplication::translate("multi_message_box", "Close", 0));
        copy_button->setText(QApplication::translate("multi_message_box", "Copy", 0));
        log_button->setText(QApplication::translate("multi_message_box", "View Log", 0));
    } // retranslateUi

};

namespace Ui {
    class multi_message_box: public Ui_multi_message_box {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTI_MESSAGE_BOX_H
