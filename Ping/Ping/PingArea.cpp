#include "PingArea.h"
PingArea::PingArea()
{
}

PingArea::PingArea(DWORD _baseIP):
	baseIP(_baseIP),
	checker(std::move(std::make_shared<Ping>()))
{
}

PingArea::~PingArea()
{
}

void PingArea::searchCtrl()
{
}
