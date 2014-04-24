#include "gui.h"
#include "manager.h"
#include <QApplication>

const QRegExp Gui::url_regex = QRegExp("((?:https?|ftp)://\\S+)");

Gui::Gui()
{
	quit_action = new QAction(tr("Quit"), this);
	connect(quit_action, SIGNAL(triggered()), this, SLOT(quit_app()));

	connect(Manager::getInstance(), SIGNAL(new_message_recived()), this, SLOT(new_message()));

	m_message_box = new multi_message_box();
	s_message_box = new single_message_box();
	main_window = new MainWindow();
	message_counter = 0;

	create_tray_icon();
	connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(tray_icon_clicked(QSystemTrayIcon::ActivationReason)));

}

//creates the system tray icon
void Gui::create_tray_icon() {
	tray_icon_menu = new QMenu();
	tray_icon_menu->addAction(quit_action);

	tray_icon = new QSystemTrayIcon();
	tray_icon->setIcon(QIcon(":/images/no_message.png"));
	tray_icon->setContextMenu(tray_icon_menu);
	tray_icon->show();
}

Gui::~Gui()
{
	delete quit_action;

	delete m_message_box;
	delete s_message_box;
	delete main_window;

	delete tray_icon;
	delete tray_icon_menu;
}

//Process user clickes on the tray icon
void Gui::tray_icon_clicked(QSystemTrayIcon::ActivationReason reason) {

	switch (reason) {
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:
		if (message_counter == 0) {
			main_window->set_combo_box(Manager::getInstance()->get_connected_computers());
			main_window->showNormal();
		}
		else if (message_counter == 1) {
			message_counter = 0;
			tray_icon->setIcon(QIcon(":/images/no_message.png"));
			s_message_box->set_message(last_message);
			s_message_box->showNormal();
		}
		else {
			m_message_box->set_message(last_message, message_counter);
			message_counter = 0;
			tray_icon->setIcon(QIcon(":/images/no_message.png"));
			m_message_box->showNormal();
		}
		break;
	default:
		;
	}
}

//This function is called when the manager is informened that there is a new message
void Gui::new_message() {
	last_message = Manager::getInstance()->get_last_message();
	message_counter++;
  if (message_counter == 1){
    tray_icon->setIcon(QIcon(":/images/one_message.png"));
  }
  else{
    tray_icon->setIcon(QIcon(":/images/multi_message.png"));
  }
}


//This function closes the application at the request of the user.
void Gui::quit_app() {
	Manager::getInstance()->close();

	qApp->quit();
}
