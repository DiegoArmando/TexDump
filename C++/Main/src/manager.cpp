#include "manager.h"
#include <thread>
#include <iostream>
#include <QApplication>
#include <QDesktopservices>
#include <QFile>
#include <QTextstream>
#include <QUrl>

//Recives a message, the last message, timestamp, and sender variables are updated and attempts to log the
//message
void Manager::receive_message(Message message) {
	this->message = message;
	this->log(message);
	
	emit new_message_recived();
}

//Returns the last message recived by the manager along with the timestap, and sender
Message Manager::get_last_message() {
	return message;

	//TO DO: this meathod is not thread safe, make it thread safe.
}

//This function tells the aplication to exit
void Manager::close() {

	//TO DO: add any code nessisary to stop the client thread.

}

//Opens the Log File
void Manager::open_log() {
	QDesktopServices::openUrl(QUrl("log.txt"));
}

//Tells the client to send message to destination
void Manager::send_message(std::string message, std::string destination) {

	//TO DO: implemnt the client, and send the message.

}

//Logs the message if log_messages is true
void Manager::log(Message message) {

	if (!get_log_message_boolean())
		return;

	QFile log(QString::fromStdString("log.txt"));
	log.open(QIODevice::Append | QIODevice::Text);
	QTextStream out(&log);

	out << QString::fromStdString(message.timestamp_ + ": " + message.sender_ + "\n");
	out << QString::fromStdString(message.text_ + "\n\n");

	log.close();
}

//This fuction is run on the Application startup to load any user settings
//Such as hot keys, wether to log messages and where to store them.
//If no user settings are found, sets them to their default values.
void Manager::load_user_settings() {
	log_messages = true;

	//TO DO: implente a users setting file, and load it
}


