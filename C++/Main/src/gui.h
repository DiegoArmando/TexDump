#ifndef TEXTDUMP_GUI_H
#define TEXTDUMP_GUI_H

#include <QOBject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QEvent>
#include <Qregexp>
#include "single_message_box.h"
#include "multi_message_box.h"
#include "mainwindow.h"
#include "message.h"

//The Gui class manages all of the graphical elements of the program, it also 
//passes on any user commands to the manager.
class Gui : public QObject
{
	Q_OBJECT
public:
	Gui();
	~Gui();

	//This is the regual expression used to itedtify URLs in text
	static const QRegExp url_regex;

	std::string get_destination() { main_window->set_combo_box(Manager::getInstance()->get_connected_computers());
									return main_window->get_destination(); }

	private slots:
	void new_message();
	void tray_icon_clicked(QSystemTrayIcon::ActivationReason reason);
	void quit_app();

private:

	int message_counter;

	single_message_box* s_message_box;
	multi_message_box* m_message_box;
	MainWindow* main_window;

	QSystemTrayIcon* tray_icon;
	QMenu* tray_icon_menu;
	QAction* quit_action;

	Message last_message;

	void create_tray_icon();
};
#endif

