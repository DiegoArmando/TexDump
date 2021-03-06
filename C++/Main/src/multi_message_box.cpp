#include "multi_message_box.h"
#include "ui_multi_message_box.h"
#include "manager.h"
#include "gui.h"

multi_message_box::multi_message_box(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::multi_message_box)
{
    ui->setupUi(this);

    ui->message_text_box->setOpenExternalLinks(true);
    ui->message_text_box->setOpenLinks(true);

    clipboard = QApplication::clipboard();

    setWindowIcon(QIcon(":/images/multi_message.png"));

    connect(ui->copy_button, SIGNAL(clicked()), this, SLOT(on_copy_button_clicked()));
    connect(ui->log_button, SIGNAL(clicked()), this, SLOT(on_log_button_clicked()));
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
  clipboard->setText(ui->message_text_box->toPlainText());
}

void multi_message_box::on_log_button_clicked()
{
	Manager::getInstance()->open_log();
}

void multi_message_box::set_message(Message message, int num_messages) {

	ui->num_messages_lable->setText(QString::fromStdString("You have recived " + std::to_string(num_messages) + " messages"));

	QString text = QString::fromStdString(message.text_).replace(Gui::url_regex, "<a href=\"\\1\">\\1</a>");
	ui->message_text_box->setText(text);
	ui->sender_timestamp_lable->setText(QString::fromStdString("")); //"from " + message.sender_ + " at " + message.timestamp_));
}
