#include "mainwindow.h"
#include "manager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(textdumpicons);

	QApplication qapp(argc, argv);
	MainWindow window;
	Manager::getInstance()->set_gui(&window);
	QApplication::setQuitOnLastWindowClosed(false);
	
	return qapp.exec();
}
