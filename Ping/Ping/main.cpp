#pragma comment(lib, "WS2_32")
#include "Controller.h"
#define TestGUI

#ifdef TestGUI
#include <QtWidgets/QApplication>
#include <qtextstream.h>
#include <iostream>
#include <qdebug.h>
#endif // PGUI
int main(int argc, char *argv[])
{
#ifdef TestGUI
	QApplication a(argc, argv);
#endif // DEBUG
	//Ping myping;
	//Sleep(1000);
	//char *ip = "114.114.114.114";
	//myping.ping(ip, 6);
	Controller c;
	c.show();

#ifdef TestGUI
	a.exec();
#endif // DEBUG
}
