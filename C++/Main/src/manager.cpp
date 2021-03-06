#include "manager.h"
#include <thread>
#include <iostream>
#include <QApplication>
#include <QDesktopservices>
#include <QFile>
#include <qsettings.h>
#include <QTextstream>
#include <QUrl>
#include "client.h"
#include "gui.h"
#include "hot_key_listener.h"

//Recives a message, and attempts to log the message
void Manager::receive_message(Message message) {
	this->message = message;
	this->log(message);
	
	emit new_message_recived();
}

//Returns the last message recived by the manager
Message Manager::get_last_message() {
	return message;

	//TO DO: this method is not thread safe, make it thread safe.
}

//This function is called when the user request the application be closed
//so any nessiary clean up can be done
void Manager::close() {
		
	hot_key_listener::getInstance()->stop();

	delete info_window;

}

//Opens the Log File
void Manager::open_log() {

	if (!QDir(log_directory).exists()) {
		QDir().mkdir(log_directory);
	}

	QFile log(QString::fromStdString(log_directory.toStdString() + "/log.txt"));
	if (!log.exists()) {
		log.open(QIODevice::Append | QIODevice::Text);
		log.close();
	}

	std::string str = "file:///" + log_directory.toStdString() + "/log.txt";
	QDesktopServices::openUrl(QUrl(QString(str.c_str())));
}

//Tells the client to send message to destination
void Manager::send_message(std::string message, std::string destination) 
{

	Client::getInstance()->sendMessage(message, destination);

}

//Logs the message if log_messages is true
void Manager::log(Message message) {

	if (!get_log_message_boolean())
		return;

	if (!QDir(log_directory).exists()) {
		QDir().mkdir(log_directory);
	}

	QFile log(QString::fromStdString(log_directory.toStdString() + "/log.txt"));
	log.open(QIODevice::Append | QIODevice::Text);
	QTextStream out(&log);

	out << QString::fromStdString(message.timestamp_ + ": " + message.sender_ + "\n");
	out << QString::fromStdString(message.text_ + "\n\n");

	log.close();
}

//This fuction is run on the Application startup to load any user settings
//Such as hot keys, whether to log messages and where to store them.
//If no user settings are found, sets them to their default values.
void Manager::load_user_settings() {
	info_window = new userinfo;
	QSettings settings("TexTeam", "TexDump");
	
	log_messages = true;

	if (!settings.contains("username")) {
		create_default_settings();
	}
	else {

		Client::getInstance()->login(settings.value("username").toString().toStdString(),
			settings.value("password").toString().toStdString(),
			settings.value("deviceName").toString().toStdString());

		log_directory = settings.value("logDirectory").toString();
	}
}

void Manager::create_default_settings() {
	QSettings settings("TexTeam", "TexDump");
	info_window->show();

	log_directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/textdump";
	settings.setValue("logDirectory", log_directory);


}

void Manager::send_hot_key_pressed(std::string text_to_send) {
	send_message(text_to_send, ((Gui*)gui)->get_destination());
}

bool Manager::login(std::string username, std::string password, std::string deviceName) {
	Client::getInstance()->login(username, password, deviceName);

	std::string error_string;
	if (Client::getInstance()->errorOccurred()) {
		error_string = Client::getInstance()->getCurrentError();
	}

	QSettings settings("TexTeam", "TexDump");

	settings.setValue("username", QString(username.c_str()));
	settings.setValue("password", QString(password.c_str()));
	settings.setValue("deviceName", QString(deviceName.c_str()));
	settings.sync();
	return true;
}

bool Manager::createUser(std::string username, std::string password, std::string deviceName, std::string email) {
	Client::getInstance()->createUser(username, password, deviceName, email);

	std::string error_string;
	if (Client::getInstance()->errorOccurred()) {
		error_string = Client::getInstance()->getCurrentError();
	}

	QSettings settings("TexTeam", "TexDump");

	settings.setValue("username", QString(username.c_str()));
	settings.setValue("password", QString(password.c_str()));
	settings.setValue("deviceName", QString(deviceName.c_str()));
	return true;
}

std::string Manager::get_computer_name() {
	QSettings settings("TexTeam", "TexDump");
	return settings.value("deviceName").toString().toStdString();
}

QStringList Manager::get_connected_computers() {
	std::vector<std::string> strings = Client::getInstance()->getDevices();

	std::string error_string;
	if (Client::getInstance()->errorOccurred()) {
		error_string = Client::getInstance()->getCurrentError();
	}

	QStringList list;

	for (int i = 0; i < strings.size(); ++i) {
		list.append(QString(strings[i].c_str()));
	}

	return list;
}

void Manager::open_login_window() {
	info_window->show();
}