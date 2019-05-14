#pragma once
#include <qgraphicsview.h>
#include <qset.h>
#include <qpixmap.h>
class Node;
class GraphWidget : public QGraphicsScene
{
	Q_OBJECT

public:
	GraphWidget(QWidget *parent = nullptr);
	//void init_all_node(QSet<int>&,const QPixmap&);
	void addNode(int , const QPixmap&);
	void addEdge(int ,int );
	void reset_pos();
	~GraphWidget();

	QSet<Node *> nodeSet;
};

