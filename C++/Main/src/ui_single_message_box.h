/********************************************************************************
** Form generated from reading UI file 'single_message_box.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLE_MESSAGE_BOX_H
#define UI_SINGLE_MESSAGE_BOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_single_message_box
{
public:
    QLabel *sender_timestam_lable;
    QTextBrowser *message_text_box;
    QPushButton *close_button;
    QPushButton *copy_button;

    void setupUi(QDialog *single_message_box)
    {
        if (single_message_box->objectName().isEmpty())
            single_message_box->setObjectName(QStringLiteral("single_message_box"));
        single_message_box->resize(400, 300);
        sender_timestam_lable = new QLabel(single_message_box);
        sender_timestam_lable->setObjectName(QStringLiteral("sender_timestam_lable"));
        sender_timestam_lable->setGeometry(QRect(60, 20, 271, 16));
        message_text_box = new QTextBrowser(single_message_box);
        message_text_box->setObjectName(QStringLiteral("message_text_box"));
        message_text_box->setGeometry(QRect(50, 40, 256, 192));
        close_button = new QPushButton(single_message_box);
        close_button->setObjectName(QStringLiteral("close_button"));
        close_button->setGeometry(QRect(50, 250, 101, 31));
        copy_button = new QPushButton(single_message_box);
        copy_button->setObjectName(QStringLiteral("copy_button"));
        copy_button->setGeometry(QRect(200, 250, 111, 31));

        retranslateUi(single_message_box);

        QMetaObject::connectSlotsByName(single_message_box);
    } // setupUi

    void retranslateUi(QDialog *single_message_box)
    {
        single_message_box->setWindowTitle(QApplication::translate("single_message_box", "TextDump", 0));
        sender_timestam_lable->setText(QApplication::translate("single_message_box", "Message from: PERSON At: TIME", 0));
        message_text_box->setHtml(QApplication::translate("single_message_box", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">I am a message</span></p></body></html>", 0));
        close_button->setText(QApplication::translate("single_message_box", "Close Window", 0));
        copy_button->setText(QApplication::translate("single_message_box", "Copy To Clip Board", 0));
    } // retranslateUi

};

namespace Ui {
    class single_message_box: public Ui_single_message_box {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLE_MESSAGE_BOX_H
