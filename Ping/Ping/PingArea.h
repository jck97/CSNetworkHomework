#pragma once
#include "Ping.h"
#include <qobject.h>
#include <qthread.h>

class PingArea : public QObject 
{
public:
	PingArea();
	PingArea(DWORD _baseIP);
	~PingArea();
	void searchCtrl();

private:
	std::shared_ptr<Ping> checker;
	DWORD baseIP;
};