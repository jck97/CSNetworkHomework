#include "edge.h"
#include "node.h"
#include <qpainter.h>
Edge::Edge(Node *r1, Node *r2)
	:p1(r1),p2(r2)
{

}

Edge::~Edge()
{
}

QRectF Edge::boundingRect() const
{
	if (!p1 || !p2)
		return QRectF();

	return QRectF(p1->pos(), p2->pos())
		.normalized()
		.adjusted(-1, -1, 1, 1);
}

void Edge::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (!p1 || !p2)
		return;
	QLineF line(p1->pos(),p2->pos());
	if (qFuzzyCompare(line.length(), qreal(0.)))
		return;
	painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter->drawLine(line);
}
