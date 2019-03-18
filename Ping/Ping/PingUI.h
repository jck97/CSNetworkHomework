#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_PingUI.h"
#include <qdebug.h>
#include "ui_MainWindow.h"
class PingUI : public QMainWindow
{
	Q_OBJECT

public:
	PingUI(QWidget *parent = Q_NULLPTR);
	Ui::MainWindow ui;
};
