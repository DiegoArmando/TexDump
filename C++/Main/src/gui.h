#ifndef TEXTDUMP_GUI_H
#define TEXTDUMP_GUI_H

#include <QOBject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QEvent>
#include "single_message_box.h"
#include "multi_message_box.h"
#include "mainwindow.h"
#include "message.h"


class Gui : public QObject
{
	Q_OBJECT
public:
	Gui();
	~Gui();

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

