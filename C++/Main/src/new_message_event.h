#ifndef NEW_MESSAGE_EVENT_H
#define NEW_MESSAGE_EVENT_H

#include <QEvent>

class new_message_event:QEvent
{
public:
	static const QEvent::Type new_message_type = static_cast<QEvent::Type>(1000);
};

#endif