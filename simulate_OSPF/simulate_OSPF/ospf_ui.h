#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ospf_ui.h"
class GraphWidget;
class ospf_ui : public QMainWindow
{
	Q_OBJECT

public:
	ospf_ui(QWidget *parent = Q_NULLPTR);
	Ui::ospf_uiClass ui;
	int port;
	void addRtItem(int, int, int, int);
	QPixmap rtPicture{":/ospf_ui/rtIcon"};
	GraphWidget *scene;
public slots:
	//[0]
	void updataRtTable(QString*msg);
	//[0]
};
