#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <qmessagebox.h>
class PingUI : public QMainWindow
{
	Q_OBJECT

public:
	PingUI(QWidget *parent = Q_NULLPTR);
	Ui::MainWindow ui;
	void winInfo(QString info);
public slots:
	void addItem(const char *IP, const unsigned int time,
		const unsigned int len, const unsigned int TTL);
};
