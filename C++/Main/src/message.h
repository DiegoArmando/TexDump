#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

//This class is used to pass around message data
class Message
{
public:
	Message() : text_(""), timestamp_(""), sender_("") {}
	Message(std::string message, std::string timestamp, std::string sender) : text_(message), timestamp_(timestamp), sender_(sender) {}
	std::string text_;
	std::string timestamp_;
	std::string sender_;

};

#endif