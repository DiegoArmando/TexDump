#include "userinfo.h"
#include "ui_userinfo.h"
#include <qvalidator>
#include "manager.h"
#include "qregexp.h"

userinfo::userinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userinfo)
{
    ui->setupUi(this);
	//setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	regex = QRegExp("[^:%;]+");
	val = new QRegExpValidator(regex, this);


	ui->password_feild->setValidator(val);
	ui->computer_feild->setValidator(val);
	ui->username_field->setValidator(val);
	ui->email_feild->setValidator(val);
}

userinfo::~userinfo()
{
	delete val;
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
		ui->email_feild->text().toStdString());

	close();
}
