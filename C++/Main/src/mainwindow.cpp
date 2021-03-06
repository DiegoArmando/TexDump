#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	ui->log_action->setChecked(Manager::getInstance()->get_log_message_boolean());

	confingure_actions();

}

//Sets up the verious menu actions
void MainWindow::confingure_actions() {
	
	toggle_log_action = new QAction(tr("Log"), this);
	toggle_log_action->setCheckable(true);
	ui->menuSettings->addAction(toggle_log_action);
	connect(toggle_log_action, SIGNAL(toggled(bool)), this, SLOT(toggle_log(bool)));


	//TO DO: right now niether of the below actions do any thing, their functionality must still be implented.
	//set_copy_close_action = new QAction(tr("Set Copy Close"),this);
	//ui->menuSettings->addAction(set_copy_close_action);

	//set_hot_key_action = new QAction(tr("Set Hot Key"), this);
	//ui->menuSettings->addAction(set_hot_key_action);
}

MainWindow::~MainWindow()
{
    delete ui;

	delete set_hot_key_action;
	delete set_copy_close_action;
}

//Tells the manager that the user has toggled save log option
void MainWindow::toggle_log(bool log) {
	Manager::getInstance()->set_log_message_boolean(log);
}

//Tells the manager to open the log
void MainWindow::on_log_button_clicked()
{
	Manager::getInstance()->open_log();
}

void MainWindow::set_combo_box(QStringList list) {
	ui->computer_list_box->clear();
	ui->computer_list_box->addItems(list);
	ui->computer_list_box->setCurrentIndex(0);
}

void MainWindow::set_computer_name(std::string name) {
	ui->your_ip_lable->setText(QString::fromStdString("Your device name: " + name));
}

//Tells the manager to send the current message
void MainWindow::on_send_button_clicked()
{
	QString Qmessage = this->ui->message_text_box->toPlainText();
	std::string message(Qmessage.toLatin1().data());

	QString Qip = this->ui->computer_list_box->currentText();
	std::string ip(Qip.toLatin1().data());

	Manager::getInstance()->send_message(message, ip);
	close();
}

std::string MainWindow::get_destination() {
	QString Qip = this->ui->computer_list_box->currentText();
	return Qip.toStdString();
}


void MainWindow::on_pushButton_clicked()
{
	Manager::getInstance()->open_login_window();
}
