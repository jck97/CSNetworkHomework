#pragma once
//�����߼������֮���Э����

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
	void searchCtrl();//�������ƺ�������ʼ����ͣ����������IP�������ť��Ӧ
signals:
	//PingReply�ĸ���������Ϊ�źŲ���
	void getRes(const char *IP, const unsigned int time,
		const unsigned int len, const unsigned int TTL);
};

