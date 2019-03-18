#pragma once
#include "Ping.h"
#include <qobject.h>
#include <qthread.h>
class PingArea : public QObject , public QThread
{
public:
	PingArea();
	PingArea(DWORD _baseIP);
	~PingArea();
	void searchArea();
	void run(); //�����̳���QThread�麯�� run()
	static void setRange(int _range) {
		range = _range;
	}
signals:
	//PingReply�ĸ�������
	void getRes(const DWORD &IP,const DWORD &time,const DWORD &len,const DWORD &TTL);

private:
	std::shared_ptr<Ping> checker;
	DWORD baseIP;
	static int range;
};