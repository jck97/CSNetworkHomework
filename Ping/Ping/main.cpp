#pragma comment(lib, "WS2_32")
#include "Controller.h"
#define TestGUI
#include <thread>
#ifdef TestGUI
#include <QtWidgets/QApplication>
#include <iostream>
#endif // PGUI
int main(int argc, char *argv[])
{
#ifdef TestGUI
	QApplication a(argc, argv);
	Controller c;
	c.show();
#endif // DEBUG

	//Ping p;
	//p.isReach("114.114.114.0");
#ifdef TestGUI
	a.exec();
#endif // DEBUG
}
