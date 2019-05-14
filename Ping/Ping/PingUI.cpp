#include "PingUI.h"
#pragma execution_character_set("utf-8")
PingUI::PingUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setObjectName("Host Finder");
	ui.resTable->setColumnCount(4);
	ui.resTable->setHorizontalHeaderLabels(
		QStringList() << "IP" << QString("����ʱ��(ms)")
		<< QString("���ĳ���(Byte)") << QString("TTL")
	);

	ui.resTable->horizontalHeader()->setSectionResizeMode(
		QHeaderView::Stretch);				//x������Ӧ���
	ui.resTable->horizontalHeader()->setSectionResizeMode(
		0, QHeaderView::ResizeToContents);	//����������Ӧ���
	ui.resTable->setSelectionBehavior(
		QAbstractItemView::SelectRows);		//ѡ������
	ui.resTable->setEditTriggers(
		QAbstractItemView::NoEditTriggers);   //��ֹ�޸�
	ui.resTable->setSelectionMode(
		QAbstractItemView::SingleSelection); //����Ϊ����ѡ�е���
	//ui.resTable->veui.resTable-rticalHeader()->setVisible(false);    //�����б�ͷ
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
