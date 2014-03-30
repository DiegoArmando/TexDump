#include "single_message_box.h"
#include "ui_single_message_box.h"

single_message_box::single_message_box(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::single_message_box)
{
    ui->setupUi(this);
}

single_message_box::~single_message_box()
{
    delete ui;
}

void single_message_box::on_copy_button_clicked()
{
    //TO DO: inplement the functionality
}

void single_message_box::on_close_button_clicked()
{
	this->close();
}

void single_message_box::set_message(Message message) {
	std::string s = message.timestamp_ + ": " + message.sender_;
	ui->sender_timestam_lable->setText(QString::fromStdString(s));
	ui->message_text_box->setText(QString::fromStdString(message.text_));
}
