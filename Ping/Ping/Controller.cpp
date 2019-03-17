#include "Controller.h"

Controller::Controller()
{
	this->logic = std::make_shared<Ping>();
	this->view = std::make_shared<PingUI>();
}


Controller::~Controller()
{
}
