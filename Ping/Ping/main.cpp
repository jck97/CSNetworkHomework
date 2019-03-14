#include "PingUI.h"
#include <QtWidgets/QApplication>
#include "Ping.h"
#include <qtextstream.h>
#include <iostream>
#include <qdebug.h>

constexpr auto DATASIZE = 32;
constexpr auto DATA = "abcdefghijklmnopqrstuvwabcdefghi";

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PingUI w;
	w.show();
	return a.exec();
}
