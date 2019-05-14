#include "ospf_node.h"
namespace ospf{

	void ospf_node::receiveLSAmsg() 
	{
		QByteArray LSAmsg;
		while (msger->hasPendingDatagrams()) {
			LSAmsg.append(msger->receiveDatagram().data());
		}
		QTextStream in(&LSAmsg, QIODevice::ReadOnly);
		int fromid;
		in >> fromid;
		//........
		int oldSize = lsas.size();
		lsas.fromQStream(in);
		if (oldSize != lsas.size())
		{
			calib_rtable();
			notify_rt_change();
		}
	}

	void ospf_node::notify_rt_change()
	{
		QString* qstr = new QString();
		QTextStream msg(qstr);
		msg << id << " ";
		rtrs.to_string(msg);
		msg.reset();
		emit rtTableChanged(qstr);
	}

	void ospf_node::exchangeLSA()
	{
		QString str;
		QTextStream out(&str,QIODevice::WriteOnly);
		out << id << " ";
		lsas.toQStream(out);
		multiSend(out.readAll().toLatin1());
	};

	void ospf_node::multiSend(QByteArray & msg)
	{
		for (auto &neighbor : ngbs.getItem())
		{
			int res = msger->writeDatagram(msg, QHostAddress::LocalHost, neighbor.id);
			//qDebug() << id << " send " << msg << " to " << neighbor.id << "res" << res;
		}
	}
	void ospf_node::calib_rtable() 
	{
		rtrs = cal_tree(lsas.getItems(), id);

		////得到节点集合
		//std::vector<LSAItem> edges(lsas.getItems());
		//std::set<int> allNode_temp;
		//for (auto &x : lsas.getItems())
		//{
		//	allNode_temp.emplace(x.r1);
		//	allNode_temp.emplace(x.r2);
		//}
		//std::vector<int> not_visit(
		//allNode_temp.begin(),allNode_temp.end()),visited;
		//int nodeSize = not_visit.size();
		//auto rtItem = rtrs.getItems();
		//rtItem.clear();
		////toid,next_hop,prev_hop,cost  first node
		//rtItem.emplace_back(id,id,id,0); 
		//auto leaving_Node = std::find(not_visit.begin(), not_visit.end(), id);
		//visited.push_back(*leaving_Node);
		//not_visit.erase(leaving_Node);
		//while (!not_visit.empty())
		//{
		//	LSAItem minDis();
		//}
	}

	RouterTable cal_tree(std::vector<LSAItem> edges,int id)
	{
		RouterTable res;
		std::vector<LSAItem> connected_edge;
		auto next_from_node = relatEdge(
		edges, id, connected_edge);
		for (auto& edge : connected_edge)
		{
			int next_hop = edge.another_rt(id);
			//int toid, int next_hop, int prev_hop, int cost
			res.push_back(next_hop, next_hop, id, edge.cost);
			res.merge(cal_sub_tree(edges, next_hop, edge.cost, next_hop));
		}
		return res;
	}

	RouterTable cal_sub_tree(std::vector<LSAItem> edges,
		int from_rt ,int cost, int next_hop)
	{
		RouterTable res;
		std::vector<LSAItem> connected_edge;
		auto next_from_node = relatEdge(edges, from_rt, connected_edge);
		for (auto& edge : connected_edge)
		{
			res.push_back(edge.another_rt(from_rt),
				next_hop, from_rt, cost + edge.cost);
		}
		for (auto& from_node : next_from_node)
		{
			auto res_temp = cal_sub_tree(edges, from_node,
			cost + get_edge_cost(connected_edge, from_node, from_rt),
			from_node);
			if (!res_temp.empty())
				res.merge(res_temp);
		}
		return res;
	}

	int get_edge_cost(
		const std::vector<LSAItem>& con_edge,
		int r1, int r2) {
		int res = 0;
		for (auto& cedge : con_edge)
		{
			if (cedge.is_same_edge(r1, r2))
			{
				res = cedge.cost;
				break;
			}
		}
		return res;
	};

	std::vector<int> relatEdge(
		std::vector<LSAItem>& edges, int from_node,
		std::vector<LSAItem>& connected_edge)
	{
		auto is_reachable = [](LSAItem& edge, int from_node) -> bool {
			return edge.r1 == from_node || edge.r2 == from_node;
		};
		std::vector<int> next_from_node;
		for (size_t i = 0; i < edges.size(); i++)
		{
			//找到可达的点，把边加入可连接边的集合，删除edges中的该边。
			auto temp_node = edges[i];
			if (is_reachable(edges[i], from_node))
			{
				next_from_node.emplace_back(temp_node.another_rt(from_node));
				
				connected_edge.emplace_back(temp_node);
				edges.erase(edges.begin() + i);
				i--;
			}
		}
		return next_from_node;
	}

	void ospf_node::add_ngb(int ngbid, int cost)
	{
		lsas.add(id, ngbid, cost);
		ngbs.add(ngbid, cost);
	}

	void ospf_node::start(int intervals)
	{
		clk->start(intervals*1000);
		calib_rtable();
		notify_rt_change();
	}

	void ospf_node::init_params()
	{
		this->msger = new QUdpSocket(this);
		if (!msger->bind(QHostAddress::LocalHost, id))
		{
			qDebug() << "failed to get port";
			exit(-1);
		};
		if (msger->state() != msger->BoundState)
			msger->bind(QHostAddress::LocalHost, id);
		clk = new QTimer(this);
		connect(clk, SIGNAL(timeout()), this, SLOT(exchangeLSA()));
		connect(msger, SIGNAL(readyRead()), this, SLOT(receiveLSAmsg()));
	}
	ospf_node::ospf_node(short port)
		:id(port)
	{
		init_params();
	}

	ospf_node::~ospf_node()
	{
	}

}
