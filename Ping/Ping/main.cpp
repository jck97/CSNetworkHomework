#pragma comment(lib, "WS2_32")
#include "Controller.h"
//#include <QtWidgets/QApplication>
//#include <qtextstream.h>
#include <iostream>
//#include <qdebug.h>

int main(int argc, char *argv[])
{
	//QApplication a(argc, argv);
	//PingUI w;
	//w.show();
	//return a.exec();
	Ping myping;
	Sleep(1000);
	char *ip = "114.114.114.114";
	myping.ping(ip,6);
}
