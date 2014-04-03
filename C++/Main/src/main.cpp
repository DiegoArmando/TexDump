#include "manager.h"
#include <QApplication>
#include <thread>
#include "client.h"
#include "gui.h"

void new_thread(void * args)
{
	((Client*)args)->listening_thread();
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
	std::thread thread(new_thread,client);
	return qapp.exec();
}
