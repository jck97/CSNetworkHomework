#pragma comment(lib, "WS2_32")
#include "Controller.h"
#include <thread>

//#define TestGUI
#define TestPing

#ifdef TestGUI
#include <QtWidgets/QApplication>
#endif // TestGUI

int main(int argc, char *argv[])
{
#ifdef TestGUI
	QApplication a(argc, argv);
	Controller c;
	c.show();
	a.exec();
#endif // TestGUI

#ifdef TestPing
	Ping p;
	p.ping("111.161.64.48", 4);
	qDebug() << sizeof(USHORT);
#endif // TestPing
}
