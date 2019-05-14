#include "PingUI.h"
#pragma execution_character_set("utf-8")
PingUI::PingUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setObjectName("Host Finder");
	ui.resTable->setColumnCount(4);
	ui.resTable->setHorizontalHeaderLabels(
		QStringList() << "IP" << QString("往返时间(ms)")
		<< QString("报文长度(Byte)") << QString("TTL")
	);

	ui.resTable->horizontalHeader()->setSectionResizeMode(
		QHeaderView::Stretch);				//x先自适应宽度
	ui.resTable->horizontalHeader()->setSectionResizeMode(
		0, QHeaderView::ResizeToContents);	//由内容自适应宽度
	ui.resTable->setSelectionBehavior(
		QAbstractItemView::SelectRows);		//选中整行
	ui.resTable->setEditTriggers(
		QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.resTable->setSelectionMode(
		QAbstractItemView::SingleSelection); //设置为可以选中单个
	//ui.resTable->veui.resTable-rticalHeader()->setVisible(false);    //隐藏列表头
}

void PingUI::addItem(const char *IP, const unsigned int time,
	const unsigned int len, const unsigned int TTL)
{
	auto table = this->ui.resTable;
	int rows = table->rowCount();
	table->insertRow(rows);
	table->setItem(rows, 0, new QTableWidgetItem(IP));
	table->setItem(rows, 1, new QTableWidgetItem(QString::number(time)));
	table->setItem(rows, 2, new QTableWidgetItem(QString::number(len)));
	table->setItem(rows, 3, new QTableWidgetItem(QString::number(TTL)));
}

void PingUI::winInfo(QString info)
{
	QMessageBox::information(this, "information", info, 
		QMessageBox::Ok, QMessageBox::Cancel);
}
