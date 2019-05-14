#pragma once
#include <qgraphicsitem.h>
#include <qlist.h>

class Edge;
class GraphWidget;
class Node : public QGraphicsPixmapItem
{
public:
	Node();
	Node(int p);
	~Node();

	int port;
};

