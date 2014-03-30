#include "hot_key_listener.h"
#include "manager.h"
#include "message.h"
#include <thread>


void hot_key_listener::run() {
	int count = 0;
	while (hot_key_listener::getInstance()->get_start()) {
		if (count % 10000 == 0)
			Manager::getInstance()->receive_message(Message("Look a hot key", "now", "The hot key manager"));
		count++;
	}
}

void hot_key_listener::start() {
	start_ = true;
}

void hot_key_listener::stop() {
	start_ = false;
}
