#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QEvent>
#include <qstandardpaths.h>
#include <qfile.h>
#include <qdir.h>
#include <stdio.h>
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
	void set_combo_box(QStringList list);
	void set_computer_name(std::string name);
	std::string get_destination();
    ~MainWindow();

private slots:
    void on_log_button_clicked();
	void on_send_button_clicked();
	void toggle_log(bool log);

    void on_pushButton_clicked();

private:
	Ui::MainWindow *ui;

	QAction* toggle_log_action;
	QAction* set_hot_key_action;
	QAction* set_copy_close_action;

	void confingure_actions();
	void new_message();


};

#endif // MAINWINDOW_H
