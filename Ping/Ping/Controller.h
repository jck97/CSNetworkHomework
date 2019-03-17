#pragma once
#include "Ping.h"
#include "PingUI.h"
#include "ui_PingUI.h"
class Controller
{
public:
	Controller();
	~Controller();
protected:
	std::shared_ptr<Ping> logic;
	std::shared_ptr<PingUI> view;
};

