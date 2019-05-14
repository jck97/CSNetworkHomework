#include "graphWidget.h"
#include <qset.h>
#include "edge.h"
#include "node.h"
#include <cmath>
GraphWidget::GraphWidget(QWidget * parent)
{
}

void GraphWidget::addNode(int p, const QPixmap & picture)
{
	bool contain{false};
	for (auto& x : nodeSet)
	{
		if (x->port == p) 
		{
			contain = true;
			break;
		}
	}
	if (!contain) {
		Node *node = new Node(p);
		node->setPixmap(picture);
		nodeSet.insert(node);
		addItem(node);
	}
}

void GraphWidget::addEdge(int p1, int p2)
{
	if (p1 == p2)
		return;
	Node *n1, *n2;
	for (auto x : nodeSet)
	{
		if (x->port == p1)
			n1 = x;
		if (x->port == p2)
			n2 = x;
	}
	if(n1 !=nullptr && n2!=nullptr)
		addItem(new Edge(n1, n2));
}

void GraphWidget::reset_pos()
{
	int count = nodeSet.size();
	int r = 100;
	float PI = 3.1415;
	int n = 0;
	float thata = 0;
	for (auto& x : nodeSet)
	{
		thata = 2 * n * PI / count;
		x->setPos(r*std::sin(thata),r*std::cos(thata));
		n++;
	}
}

GraphWidget::~GraphWidget()
{
}
