#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include "mainwindow.h"
#include "message.h"

// The manager is a singlton class that manages comunication between the client
// and the GUI. It is also in charge of handling any user requests generated from the GUI
// such as opening the log file, or closing the application.
class Manager
{

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

private:
	QObject* gui;
	Manager(void) : message("HI", "1:20pm", "000.001.0002.0003") { load_user_settings(); }
	Manager(Manager const&);
	void operator=(Manager const&);
	void load_user_settings();
	void log(Message message);

	bool log_messages;
	Message message;
	
};

#endif
