#include "PingUI.h"
#pragma execution_character_set("utf-8")
PingUI::PingUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setObjectName("Host Finder");
	ui.resTable->setColumnCount(4);
	ui.resTable->setHorizontalHeaderLabels(
		QStringList() << "IP" << QString("路由距离"));
	ui.resTable->setSelectionBehavior(QAbstractItemView::SelectRows);  //选中整行
	ui.resTable->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.resTable->setSelectionMode(QAbstractItemView::SingleSelection); //设置为可以选中单个
	//ui.resTable->veui.resTable-rticalHeader()->setVisible(false);      //隐藏列表头
	
}
