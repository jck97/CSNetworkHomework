#include "node.h"
#include "edge.h"
#include "graphWidget.h"

Node::Node()
	:port(-1)
{
}

Node::Node(int p)
	:port(p)
{
}

Node::~Node()
{
}
