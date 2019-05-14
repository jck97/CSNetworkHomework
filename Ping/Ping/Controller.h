#pragma once
//负责逻辑与界面之间的协作。

#include "PingArea.h"
#include "PingUI.h"
#include <qobject.h>
#include <thread>
#include <mutex>
#include <condition_variable>

class Controller : public QObject
{
	Q_OBJECT

public:
	Controller();
	~Controller();
	void show();
protected:
	std::thread *t;
	std::unique_ptr<PingArea> logic;
	std::unique_ptr<PingUI> view;
	void startSeaching();
	void searchArea(const DWORD baseIP);
	void reSearch();
public slots:
	void searchCtrl();//搜索控制函数。开始和暂停搜索，更换IP。点击按钮响应
signals:
	//PingReply的各个属性作为信号参数
	void getRes(const char *IP, const unsigned int time,
		const unsigned int len, const unsigned int TTL);
};

