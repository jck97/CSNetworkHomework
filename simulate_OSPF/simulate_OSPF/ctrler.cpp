#include "ctrler.h"
#include <qfile.h>
#include <qtextstream.h>
ctrler::ctrler()
	:view(std::make_unique<ospf_ui>())
{
}

ctrler::~ctrler()
{
}

void ctrler::initNet(QString filename)
{
	using namespace ospf;
	dataFromFile(filename);
	this->view->port = router->id;
	this->view->setWindowTitle(QString("router ")+QString::number(router->id));
	QObject::connect(router.get(), &ospf_node::rtTableChanged,
		view.get(), &ospf_ui::updataRtTable);
	router->notify_rt_change();
}

void ctrler::start()
{
}

void ctrler::show()
{
	view->show();
	router->start(10);
}

void ctrler::dataFromFile(QString filename)
{
	int nbs_num, cost, id;
	QFile infile(filename);
	if (!infile.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		qDebug() << "open file failed!";
		return;
	}
	QTextStream in(&infile);
	in >> id;
	router = std::make_unique<ospf::ospf_node>(id);
	in >> nbs_num;
	for (size_t i = 0; i < nbs_num; i++)
	{
		in >> id >> cost;
		router->add_ngb(id, cost);
	}
}

void ctrler::connetAll()
{

}
