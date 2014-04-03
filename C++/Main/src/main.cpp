#include "manager.h"
#include <QApplication>
#include <thread>
#include "client.h"
#include "gui.h"

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(textdumpicons);

	QApplication qapp(argc, argv);
	Gui gui;
	Manager::getInstance()->set_gui(&gui);
	QApplication::setQuitOnLastWindowClosed(false);

	Client* client = Client::getInstance();
	client->init();

	return qapp.exec();
}
