#pragma once
#include <set>
namespace ospf 
{
	class ngrItem {
	public:
		ngrItem() {};
		ngrItem(int n, int c, int ttl = 60)
			:id(n), cost(c), TTL(ttl)
		{};
		ngrItem(int n)
			:id(n), cost(999999), TTL(60)
		{};
		friend inline bool operator<(const ngrItem& lth, const ngrItem& rth)
		{
			return lth.id < rth.id;
		};
		friend inline bool operator>(const ngrItem& lth, const ngrItem& rth)
		{
			return lth.id > rth.id;
		};
		friend inline bool operator==(const ngrItem& lth, const ngrItem& rth)
		{
			return lth.id == rth.id;
		}
		int id;//port
		int cost;
		int TTL;
	};

	class neighborTable
	{
	public:
		neighborTable();
		void add(int id, int cost);
		void add(int id);
		bool contain(int id);
		std::set<ngrItem>& getItem()
		{
			return items;
		}
		~neighborTable();
	private:
		std::set<ngrItem> items;
	};
}
