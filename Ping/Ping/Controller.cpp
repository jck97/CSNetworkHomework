#include "Controller.h"
Controller::Controller():
	searching(false),
	logic(std::move(std::make_shared<PingArea>())),
	view(std::move(std::make_shared<PingUI>()))
{
}


Controller::~Controller()
{
}

void Controller::addItem(const DWORD & time, const DWORD & len, const DWORD & TTL)
{
	auto table = view->ui.resTable;
	int rows = table->rowCount();
	table->insertRow(rows);

}

void Controller::show()
{
	view->show();
}
