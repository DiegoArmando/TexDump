#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <QObject>
#include <qsettings.h>
#include "message.h"
#include "userinfo.h"

// The manager is a singlton class that manages comunication between the client
// and the GUI. It is also in charge of handling any user requests generated from the GUI
// such as opening the log file, or closing the application.
class Manager: public QObject
{
	Q_OBJECT

public:

	static Manager* getInstance() {
		static Manager manager;
		return &manager;
	}

	void receive_message(Message message);
	Message get_last_message();
	void open_log();
	void send_message(std::string message, std::string destination);
    void close();
	bool get_log_message_boolean() { return log_messages; }
	void set_log_message_boolean(bool log_messages) { this->log_messages = log_messages; }
	void set_gui(QObject* object) { gui = object; }
	void send_hot_key_pressed(std::string text_to_send);

	bool login(std::string username, std::string password, std::string deviceName);
	bool createUser(std::string username, std::string password, std::string deviceName, std::string email);

	void open_login_window();
	QStringList get_connected_computers();

	std::string get_computer_name();

signals:
	void new_message_recived();

private:
	QObject* gui;
	Manager(void) : message("HI", "1:20pm", "000.001.0002.0003") { load_user_settings(); }
	Manager(Manager const&);
	void operator=(Manager const&);
	void load_user_settings();
	void create_default_settings();
	void log(Message message);

	bool log_messages;
	Message message;
	QString log_directory;
	userinfo* info_window;
	
};

#endif
