#pragma once
#include <vector>
#include <qtextstream.h>
namespace ospf {
	class rtItem
	{
	public:
		//toid,next_hop,prev_hop,cost
		//Ŀ�Ľڵ㣬��һ����ͨ���ĸ��ڵ㵽��Ŀ�Ľڵ㣬������
		rtItem(int to,int next,int prev,int c)
			:toId(to),next_hop(next),prev_hop(prev),cost(c)
		{}

		int toId;
		int next_hop;
		int prev_hop;
		int cost;
	};
	class RouterTable
	{
	public:
		void push_back(int toid, int next_hop, int prev_hop, int cost);
		void merge(RouterTable& rt);
		QTextStream& to_string(QTextStream& out);

		RouterTable();
		~RouterTable();


		std::vector<rtItem>& getItems()
		{
			return items;
		}
		bool empty()
		{
			return items.empty();
		}
		int size()
		{
			return items.size();
		}

	private:
		std::vector<rtItem> items;
	};
}