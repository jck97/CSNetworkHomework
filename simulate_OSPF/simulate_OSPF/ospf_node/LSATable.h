#pragma once
#include <vector>
#include <algorithm>
#include <qtextstream.h>
namespace ospf {

	class LSAItem
	{
	public:
		LSAItem(int _r1, int _r2, int _cost)
			:r1(_r1), r2(_r2), cost(_cost)
		{
		}
		bool is_same_edge(int rr1, int rr2) const
		{
			return (r1 == rr1 && r2 == rr2)
				|| (r1 == rr2 && r2 == rr1);
		}
		bool is_same_edge(const LSAItem& rth) const
		{
			//默认两个节点来回消费相同
			return (r1 == rth.r1 && r2 == rth.r2)
				|| (r1 == rth.r2 && r2 == rth.r1);
		}
		friend bool operator==(const LSAItem& lth, const LSAItem& rth)
		{
			return ((lth.r1 == rth.r1) && (lth.r2 == rth.r2))
				|| ((lth.r1 == rth.r2) && (lth.r2 == rth.r1));
		}
		int another_rt(int oneid)
		{
			return r1 == oneid ? r2 : r1;
		};
		int r1;
		int r2;
		int cost;
	};
	class LSATable
	{
	public:
		LSATable();
		void add(int, int, int)noexcept;
		std::vector<LSAItem>& getItems() noexcept
		{
			return items;
		};
		size_t size()
		{
			return items.size();
		}
		void toQStream(QTextStream&);
		void fromQStream(QTextStream&);
		~LSATable();
	private:
		std::vector<LSAItem> items;
	};

}
