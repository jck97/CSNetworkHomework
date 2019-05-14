#include "LSATable.h"
namespace ospf {
	LSATable::LSATable()
	{
	}
	void LSATable::add(int r1,int r2, int cost) noexcept
	{
		LSAItem newItem(r1,r2,cost);
		auto temp = std::find_if(std::begin(items), std::end(items),
			[&newItem](auto& x)->bool {return newItem.is_same_edge(x); });
		if (temp == std::end(items))
		{
			items.emplace_back(std::move(newItem));
		}
		//else
		//{
		//	temp->cost = cost;
		//	changed = true;
		//}
	}
	void LSATable::toQStream(QTextStream& out)
	{	
		out << items.size() << " ";
		for (auto &item : items)
		{
			out << item.r1 << " " << item.r2 << " " << item.cost << " ";
		}
	}
	void LSATable::fromQStream(QTextStream &in)
	{
		int lsaItemNum;
		int rt1, rt2, edgeLen;
		in >> lsaItemNum;
		for (size_t i = 0; i < lsaItemNum; i++)
		{
			in >> rt1 >> rt2 >> edgeLen;
			add(rt1, rt2, edgeLen);
		}
	}
	LSATable::~LSATable()
	{
	}
}