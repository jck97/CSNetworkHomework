#include "RouterTable.h"


namespace ospf{
	void RouterTable::push_back(int toid, int next_hop, int prev_hop, int cost)
	{
		return items.emplace_back(toid, next_hop, prev_hop, cost);
	}
	void RouterTable::merge(RouterTable & rt)
	{
		for (auto& r : rt.items)
		{
			items.push_back(r);
		}
	}
	QTextStream & RouterTable::to_string(QTextStream & out)
	{
		out << items.size() << " ";
		for (auto& x : items)
		{
			out << x.toId << " " << x.next_hop << " " << x.prev_hop << " " << x.cost << " ";
			//out << "to:" << x.toId << " next_hop:" << x.next_hop
			//	<< " prev:" << x.prev_hop << " cost:" << x.cost << endl;
		}
		return out;
	}
	RouterTable::RouterTable()
{
}


RouterTable::~RouterTable()
{
}
}
