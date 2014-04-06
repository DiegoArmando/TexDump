#include "single_message_box.h"
#include "gui.h"
#include "ui_single_message_box.h"

single_message_box::single_message_box(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::single_message_box)
{
    ui->setupUi(this);

	ui->message_text_box->setOpenExternalLinks(true);
	ui->message_text_box->setOpenLinks(true);

  clipboard = QApplication::clipboard();

  setWindowIcon(QIcon(":/images/one_message.png"));

  connect(ui->copy_button, SIGNAL(clicked()), this, SLOT(on_copy_button_clicked()));
}

single_message_box::~single_message_box()
{
    delete ui;
}

void single_message_box::on_copy_button_clicked()
{
  clipboard->setText(ui->message_text_box->toPlainText());
}

void single_message_box::on_close_button_clicked()
{
	this->close();
}

void single_message_box::set_message(Message message) {
	std::string s = message.timestamp_ + ": " + message.sender_;
	ui->sender_timestam_lable->setText(QString::fromStdString(s));
	
	QString text = QString::fromStdString(message.text_).replace(Gui::url_regex, "<a href=\"\\1\">\\1</a>");
	ui->message_text_box->setText(text);
}
