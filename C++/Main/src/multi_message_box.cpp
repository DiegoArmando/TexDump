#include "multi_message_box.h"
#include "ui_multi_message_box.h"
#include "manager.h"

multi_message_box::multi_message_box(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::multi_message_box)
{
    ui->setupUi(this);
}

multi_message_box::~multi_message_box()
{
    delete ui;
}

void multi_message_box::on_close_button_clicked()
{
	this->close();
}

void multi_message_box::on_copy_button_clicked()
{
    //TO DO: implement functionality
}

void multi_message_box::on_log_button_clicked()
{
	Manager::getInstance()->open_log();
}

void multi_message_box::set_message(Message message, int num_messages) {

	ui->num_messages_lable->setText(QString::fromStdString("You have recived " + std::to_string(num_messages) + " messages"));
	ui->message_text_box->setText(QString::fromStdString(message.text_));
	ui->sender_timestamp_lable->setText(QString::fromStdString("from " + message.sender_ + " at " + message.timestamp_));
}
