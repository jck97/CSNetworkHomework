#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PingUI.h"

class PingUI : public QMainWindow
{
	Q_OBJECT

public:
	PingUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::PingUIClass ui;
};
