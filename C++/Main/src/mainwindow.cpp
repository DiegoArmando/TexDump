#include "mainwindow.h"
#include "ui_mainwindow.h"

// The MainWindow class is the main gui element, it handles all user interaction that is not related
// to showing recieved messages.
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->destination_ip_text_box->setInputMask(QString("000.000.000.000"));
	ui->destination_ip_text_box->setText(QString("000.000.000.000"));
	ui->log_action->setChecked(Manager::getInstance()->get_log_message_boolean());

	m_message_box = new multi_message_box();
	s_message_box = new single_message_box();
	message_counter = 0;

	confingure_actions();
	create_tray_icon();

	connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(tray_icon_clicked(QSystemTrayIcon::ActivationReason)));
}

//creates the tray icon
void MainWindow::create_tray_icon() {
	tray_icon_menu = new QMenu(this);
	tray_icon_menu->addAction(quit_action);

	tray_icon = new QSystemTrayIcon();
	tray_icon->setIcon(QIcon(":/images/bad.png"));
	tray_icon->setContextMenu(tray_icon_menu);
	tray_icon->show();
}

void MainWindow::confingure_actions() {
	quit_action = new QAction(tr("Quit"), this);
	connect(quit_action, SIGNAL(triggered()), this, SLOT(quit_app()));
	
	toggle_log_action = new QAction(tr("Log"), this);
	toggle_log_action->setCheckable(true);
	ui->menuSettings->addAction(toggle_log_action);
	connect(toggle_log_action, SIGNAL(toggled(bool)), this, SLOT(toggle_log(bool)));


	//TO DO: right now niether of the below actions do any this, their functionaluty must still be implented.
	set_copy_close_action = new QAction(tr("Set Copy Close"),this);
	ui->menuSettings->addAction(set_copy_close_action);

	set_hot_key_action = new QAction(tr("Set Hot Key"), this);
	ui->menuSettings->addAction(set_hot_key_action);
}

MainWindow::~MainWindow()
{
    delete ui;
	delete tray_icon;
	delete tray_icon_menu;

	delete m_message_box;
	delete s_message_box;

	delete quit_action;
	delete set_hot_key_action;
	delete set_copy_close_action;
}

//Process user clickes on the tray icon
void MainWindow::tray_icon_clicked(QSystemTrayIcon::ActivationReason reason) {
	
	switch (reason) {
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:
		if (message_counter == 0) {
			showNormal();
		}
		else if (message_counter == 1) {
			message_counter = 0;
			s_message_box->set_message(Manager::getInstance()->get_last_message());
			s_message_box->showNormal();
		}
		else {
			//m_message_box->set_message(Manager::getInstance()->get_last_message(), message_counter);
			m_message_box->set_message(Manager::getInstance()->get_last_message(), message_counter);
			message_counter = 0;
			m_message_box->showNormal();
		}
		break;
	default:
		;
	}
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

//Tells the manager to send the current message
void MainWindow::on_send_button_clicked()
{
	QString Qmessage = this->ui->message_text_box->toPlainText();
	std::string message(Qmessage.toLatin1().data());

	QString Qip = this->ui->destination_ip_text_box->text();
	std::string ip(Qip.toLatin1().data());

	Manager::getInstance()->send_message(message, ip);
	
}

//This function closes the application at the request of the user.
void MainWindow::quit_app() {
	Manager::getInstance()->close();

	qApp->quit();
}

//Recieves and processes the new message event;
bool MainWindow::event(QEvent* event) {
	if (event->type() == MainWindow::new_message_type) {
		message_counter++;
	}	
	return QMainWindow::event(event);
}

