#include "PingUI.h"
#pragma execution_character_set("utf-8")
PingUI::PingUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setObjectName("Host Finder");
	ui.resTable->setColumnCount(4);
	ui.resTable->setHorizontalHeaderLabels(
		QStringList() << "IP" << QString("·�ɾ���"));
	ui.resTable->setSelectionBehavior(QAbstractItemView::SelectRows);  //ѡ������
	ui.resTable->setEditTriggers(QAbstractItemView::NoEditTriggers);   //��ֹ�޸�
	ui.resTable->setSelectionMode(QAbstractItemView::SingleSelection); //����Ϊ����ѡ�е���
	//ui.resTable->veui.resTable-rticalHeader()->setVisible(false);      //�����б�ͷ
	
}
