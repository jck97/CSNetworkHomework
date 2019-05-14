#include "neighborTable.h"

namespace ospf
{
neighborTable::neighborTable()
{

}

void neighborTable::add(int id, int cost)
{
	items.emplace(id, cost);
}

void neighborTable::add(int id)
{
	items.emplace(id);
}

bool neighborTable::contain(int id)
{
	return items.end() != std::find(
		items.begin(),items.end(),ngrItem(id));
}

neighborTable::~neighborTable()
{
}

}
