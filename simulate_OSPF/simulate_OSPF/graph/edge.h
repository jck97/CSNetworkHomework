#pragma once
#include <qgraphicsitem.h>
class Node;
class Edge :public QGraphicsItem
{
public:
	Edge(Node *,Node *);
	~Edge();
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	Node *p1, *p2;
};

