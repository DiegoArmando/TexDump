#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QEvent>
#include "manager.h"
#include "single_message_box.h"
#include "multi_message_box.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

	static const QEvent::Type new_message_type = static_cast<QEvent::Type>(1000);

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	bool event(QEvent* event);

private slots:
    void on_log_button_clicked();
	void on_send_button_clicked();
	void quit_app();
	void toggle_log(bool log);
	void tray_icon_clicked(QSystemTrayIcon::ActivationReason reason);

private:
	Ui::MainWindow *ui;
	QSystemTrayIcon *tray_icon;
	QMenu* tray_icon_menu;

	single_message_box* s_message_box;
	multi_message_box* m_message_box;
	int message_counter;

	QAction* toggle_log_action;
	QAction* set_hot_key_action;
	QAction* set_copy_close_action;
	QAction* quit_action;

	void create_tray_icon(); 
	void confingure_actions();
	void new_message();


};

#endif // MAINWINDOW_H
