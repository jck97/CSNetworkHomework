#include "ospf_ui.h"
#include <qdebug.h>
#include <qmessagebox.h>
#include "graph/graphWidget.h"
#include <QRandomGenerator>
#include <qgraphicsview.h>

ospf_ui::ospf_ui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	scene = new GraphWidget(ui.rtGraphics);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	scene->setSceneRect(-200, -200, 400, 400);
	ui.rtGraphics->setScene(scene);
	ui.rtGraphics->setRenderHint(QPainter::Antialiasing);


	ui.rtTable->setColumnCount(4);
	ui.rtTable->setHorizontalHeaderLabels(
		QStringList() << "router id" << QString("next hop")
		<< QString("prev hop") << QString("cost")
	);

	ui.rtTable->horizontalHeader()->setSectionResizeMode(
		QHeaderView::Stretch);				//x先自适应宽度
	ui.rtTable->horizontalHeader()->setSectionResizeMode(
		0, QHeaderView::ResizeToContents);	//由内容自适应宽度
	ui.rtTable->setSelectionBehavior(
		QAbstractItemView::SelectRows);		//选中整行
	ui.rtTable->setEditTriggers(
		QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.rtTable->setSelectionMode(
		QAbstractItemView::SingleSelection); //设置为可以选中单个
}
void ospf_ui::updataRtTable(QString *msg)
{
	ui.rtTable->setRowCount(0);
	QTextStream in(msg);
	int fromId;
	int	rt_count;
	
	in >> fromId >> rt_count;
	scene->addNode(fromId,rtPicture);

	int to{ 0 }, next_hop{ 0 }, prev_hop{ 0 }, cost{ 0 };
	for (size_t i = 0; i < rt_count; i++)
	{
		in >> to >> next_hop >> prev_hop >> cost;
		if(in.status() == QTextStream::Ok) 
		{
			addRtItem(to, next_hop, prev_hop, cost);
			scene->addNode(to, rtPicture);
			scene->addNode(next_hop, rtPicture);
			scene->addNode(prev_hop, rtPicture);
			scene->addEdge(prev_hop, to);
		}
	}
	scene->reset_pos();
	ui.rtGraphics->viewport()->update();
	delete msg;
}

void ospf_ui::addRtItem(int to, int next_hop, int prev_hop, int cost)
{
	auto table = this->ui.rtTable;
	int rows = table->rowCount();
	table->insertRow(rows);
	table->setItem(rows, 0, new QTableWidgetItem(QString::number(to)));
	table->setItem(rows, 1, new QTableWidgetItem(QString::number(next_hop)));
	table->setItem(rows, 2, new QTableWidgetItem(QString::number(prev_hop)));
	table->setItem(rows, 3, new QTableWidgetItem(QString::number(cost)));
}