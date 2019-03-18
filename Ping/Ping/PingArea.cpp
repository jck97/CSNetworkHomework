#include "PingArea.h"
int PingArea::range = 16;
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

void PingArea::searchArea()
{
}

void PingArea::run()
{
	for (size_t i = 0; i < range; i++)
	{
		DWORD IP = baseIP + i;
		if (checker->isReach(IP))
		{
			emit getRes(IP,
				checker->getReply()->time,
				checker->getReply()->dataLen,
				checker->getReply()->TTL
			);
			this->sleep(10);
			this->wait();
			
		}
	}
}
