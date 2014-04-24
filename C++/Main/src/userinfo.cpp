#include "userinfo.h"
#include "ui_userinfo.h"
#include "qvalidator.h"
#include "manager.h"

userinfo::userinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userinfo)
{
    ui->setupUi(this);
	//setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	ui->password_feild->setInputMask("Nnnnnnnnnnnn");
	ui->password_feild->setText("");
	ui->computer_feild->setInputMask("Nnnnnnnnnnnn");
	ui->computer_feild->setText("");
	ui->username_field->setInputMask("Nnnnnnnnnnnn");
	ui->username_field->setText("");
}

userinfo::~userinfo()
{
    delete ui;
}

void userinfo::on_login_button_clicked()
{
	Manager::getInstance()->login(ui->username_field->text().toStdString(),
		ui->password_feild->text().toStdString(),
		ui->computer_feild->text().toStdString());

	close();
}

void userinfo::on_register_button_clicked()
{
	Manager::getInstance()->createUser(ui->username_field->text().toStdString(),
		ui->password_feild->text().toStdString(),
		ui->computer_feild->text().toStdString(),
		"");

	close();
}
