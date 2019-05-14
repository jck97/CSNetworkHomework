#include <qapplication.h>
#include <qdebug.h>
#include <qstring.h>
#include <qprocess.h>

QString baseRtData("../simulate_OSPF/rtData/r");
QString OSPF("./simulate_OSPF.exe");
QString OSPF2("../x64/Debug//simulate_OSPF.exe");

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QProcess process[5];
	for (size_t i = 1; i < 6; i++)
	{
		QString param = baseRtData + QString::number(i) + ".txt";
		process[i-1].start(OSPF2, QStringList() << param);
	}

	return a.exec();
}
