#pragma once
//负责逻辑与界面之间的协作。

#include "PingArea.h"
#include "PingUI.h"
#include "ui_PingUI.h"
class Controller
{
public:
	Controller();
	~Controller();
	void addItem(const DWORD &time, const DWORD &len, const DWORD &TTL);
	void show();
protected:
	bool searching;
	std::shared_ptr<PingArea> logic;
	std::shared_ptr<PingUI> view;
};

