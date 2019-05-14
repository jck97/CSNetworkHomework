#pragma once
#include "RouterTable.h"
#include "neighborTable.h"
#include "LSATable.h"
#include <QtNetwork/qudpsocket.h>
#include <qobject.h>
#include <qtimer.h>
#include <QtNetwork/qnetworkdatagram.h>

namespace ospf {
	class ospf_node :public QObject
	{
		Q_OBJECT
	public:
		int id;				//port
		LSATable lsas;
		neighborTable ngbs;
		RouterTable rtrs;
		QUdpSocket *msger;
		QTimer *clk;
		ospf_node(short port);
		~ospf_node();
		void multiSend(QByteArray&);
		void add_ngb(int,int);
		void start(int intervals);
		void calib_rtable();//调整路由表
		void notify_rt_change();
	private:
		void init_params();
	signals:
		void rtTableChanged(QString*);
	public slots:
		void exchangeLSA();
		void receiveLSAmsg();
	};
	RouterTable cal_tree(std::vector<LSAItem> edges, int id);

	RouterTable cal_sub_tree(std::vector<LSAItem> edges,
		int from_rt, int cost, int next_hop);

	int get_edge_cost(const std::vector<LSAItem>& con_edge,
		int r1, int r2);

	std::vector<int> relatEdge(
		std::vector<LSAItem>& edges, int from_node,
		std::vector<LSAItem>& connected_edge);
}

