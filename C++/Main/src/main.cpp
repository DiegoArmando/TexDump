#include "manager.h"
#include <QApplication>
#include <thread>
#include "client.h"
#include "gui.h"
#include "hot_key_listener.h"

void new_thread(void * args) {
	((Client*)args)->listening_thread();
}

void start_hot_key_thread(void * args) {
	((hot_key_listener*)args)->run();
}

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(textdumpicons);

	QApplication qapp(argc, argv);
	Gui gui;
	Manager::getInstance()->set_gui(&gui);
	QApplication::setQuitOnLastWindowClosed(false);

	Client* client = Client::getInstance();
	client->init();

	hot_key_listener* hotkey = hot_key_listener::getInstance();

	std::thread thread(new_thread,client);
	std::thread hkthread(start_hot_key_thread, hotkey);
	return qapp.exec();
}
