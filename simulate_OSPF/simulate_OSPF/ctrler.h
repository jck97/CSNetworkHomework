#pragma once
#include "ospf_ui.h"
#include <memory>
#include "ospf_node/ospf_node.h"
#include <qprocess.h>
class ctrler
{
public:
	ctrler();
	~ctrler();
	void start();
	void initNet(QString filename);
	std::unique_ptr<ospf_ui> view;
	std::unique_ptr<ospf::ospf_node> router;
	void show();
private:
	void dataFromFile(QString filename);
	void connetAll();
};