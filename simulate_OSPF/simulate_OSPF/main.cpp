#include "ospf_ui.h"
#include "ctrler.h"
#include <QtWidgets/QApplication>
#include <qstring.h>
#include <qprocess.h>
#include "ospf_node//ospf_node.h"
#include <qfile.h>
#include <iostream>

int main(int argc, char *argv[])
{
	QString filename = "rtData/r0.txt";
	if (argc == 2)
	{
		filename.clear();
		filename.append(argv[1]);
	}
	QApplication app(argc, argv);
	ctrler ctr1;
	ctr1.initNet(filename);
	ctr1.show();
	app.exec();
}

/*

//QString ss;
//QTextStream s(&ss);
//for (size_t i = 0; i < 10; i++)
//{
//	s << i;
//}
//qDebug() << s.readAll().toLatin1();

//void test_ospfnode_cal_tree()
//{
//	ospf::ospf_node node(7781);
//	node.lsas.add(7777, 7778, 1);
//	node.lsas.add(7778, 7779, 10);
//	node.lsas.add(7779, 7780, 100);
//	node.lsas.add(7781, 7779, 1000);
//	node.calib_rtable();
//	QString str;
//	QTextStream out(&str, QIODevice::Text);
//	node.rtrs.to_string(out);
//	qDebug().noquote() << str;
//}

/*

	//taskkill /f /t /im  simulate_OSPF.exe
	//QApplication a(argc,argv);
	//ctrler c;
	//c.initNet("rtData.txt");
	//c.show();
	//a.exec();

	//QProcess process;
	//process.setEnvironment(QProcess::systemEnvironment());
	//process.start("pkexec --user root ", QStringList() << QString("apt-get install xyz"));
	//process.waitForFinished();
	//process.close();
	QProcess p;
	p.setEnvironment(QProcess::systemEnvironment());
	//p.setCreateProcessArgumentsModifier([](QProcess::CreateProcessArguments *args)
	//{
	//	args->flags |= CREATE_NEW;
	//});
	p.start(ping);
	Sleep(1000000);
	p.close();
	//QProcess process;
	//process.setCreateProcessArgumentsModifier([](QProcess::CreateProcessArguments *args)
	//{
	//	args->flags |= CREATE_NEW_CONSOLE;
	//	args->startupInfo->dwFlags &= ~STARTF_USESTDHANDLES;
	//	args->startupInfo->dwFlags |= STARTF_USEFILLATTRIBUTE;
	//	args->startupInfo->dwFillAttribute = BACKGROUND_BLUE | FOREGROUND_RED
	//		| FOREGROUND_INTENSITY;
	//});
	//process.start("C:\\Windows\\System32\\cmd.exe", QStringList() << "/k" << "title" << "The Child Process");
	//process.waitForFinished();
*/