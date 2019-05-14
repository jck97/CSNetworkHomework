#include "Controller.h"
#pragma execution_character_set("utf-8")
namespace ctrlpm //全局变量，用于线程协调
{
	std::mutex mtx;
	std::condition_variable cv;
	bool isSearching = false;//开始暂停搜索
	DWORD baseIP = 0;
	bool stop = false;//结束搜索
	constexpr auto range4Thread = 64;
	constexpr auto IPRange = 256;
};

Controller::Controller():
	logic(std::move(std::make_unique<PingArea>())),
	view(std::move(std::make_unique<PingUI>()))
{
	QObject::connect(this, &Controller::getRes, 
		view.get(), &PingUI::addItem);
	QObject::connect(view->ui.button, &QPushButton::clicked,
		this, &Controller::searchCtrl);
}

Controller::~Controller()
{
	if (t != nullptr) {
		//结束可能处于阻塞阶段的线程
		ctrlpm::stop = true;
		ctrlpm::isSearching = true;
		ctrlpm::cv.notify_all();
		for (size_t i = 0; i < ctrlpm::IPRange/ctrlpm::range4Thread; i++)
		{
			//联结线程
			if (t[i].joinable())
			{
				t[i].join();
			}
		}
		delete[]t;
	}
}

void Controller::startSeaching()
{
	auto thread_size = ctrlpm::IPRange / ctrlpm::range4Thread;
	t = new std::thread[thread_size];
	for (size_t i = 0; i < thread_size; i++)
	{
#ifdef RTP_BIG_ENDIAN//大端机与小端机ip的计算有点差别
		int baseip = ctrlpm::baseIP + i * ctrlpm::range4Thread;
#else  
		int baseip = ctrlpm::baseIP + i * ctrlpm::range4Thread*(1<<24);
#endif
		t[i] = std::thread(
			[this,baseip]() {this->searchArea(baseip); }
		);
	}
}

void Controller::searchCtrl()
{
	std::unique_lock<std::mutex> lck(ctrlpm::mtx);	//锁互斥量。									//当前互斥量应该没有被锁定
	bool oldSearching = ctrlpm::isSearching;
	ctrlpm::isSearching = false;					//阻塞搜索线程
	QString strIP = view->ui.input->text();
	strIP += ".0";
	auto inputIP = inet_addr(strIP.toStdString().c_str());
	if (inputIP == INADDR_NONE) {
		//输入IP不可用，没有开启线程
		view->winInfo(QString("get error ip,try again!"));
	}
	else if(ctrlpm::baseIP == 0)
	{
		//第一次搜索，不停止，不阻塞
		ctrlpm::baseIP = inputIP;
		ctrlpm::stop = false;
		ctrlpm::isSearching = true;
		view->winInfo(QString("searching: ip from ") 
			+ strIP +QString(" \nto ")+ view->ui.input->text()+".255");
		startSeaching();
		view->ui.button->setText("暂停");
	}
	else if (inputIP != ctrlpm::baseIP)
	{
		//更换了目标IP，不停止，不阻塞
		ctrlpm::stop = false;
		ctrlpm::isSearching = true;
		view->ui.resTable->setRowCount(0);
		ctrlpm::baseIP = inputIP;
		reSearch();
		view->winInfo(QString("searching ip from ")
			+ strIP + QString(" \nto ") + view->ui.input->text() + ".225");
	}
	else
	{
		//暂停与继续的转换
		ctrlpm::isSearching = !oldSearching;
		if (ctrlpm::isSearching) {
			view->ui.button->setText("暂停");
		}
		else 
		{
			view->ui.button->setText("继续");
		}
	}
	lck.unlock();
	ctrlpm::cv.notify_all();
}

void Controller::searchArea(const DWORD baseIP)
{
	size_t i = 0;
	Ping checker;
	u_long ip;
	in_addr in;
	memset((char*)&in, 0, sizeof(in));
	while (!ctrlpm::stop && i++ <ctrlpm::range4Thread) {
#ifdef RTP_BIG_ENDIAN   //BE   大端机与小端机ip的计算有点差别
		ip = baseIP + i;
#else					//LE
		ip = (DWORD)(baseIP + (i << 24));
#endif
		//仅仅为了实现暂停功能，需要进一步优化
		std::unique_lock<std::mutex> lck(ctrlpm::mtx);
		ctrlpm::cv.wait(lck, []() {return ctrlpm::isSearching; });
		lck.unlock();
		ctrlpm::cv.notify_all();

		if (checker.isReach(ip))
		{
			auto rpy = checker.getReply();
			in.S_un.S_addr = ip;
			qDebug() << "ip: " << inet_ntoa(in) << " "; rpy->print();
			emit getRes(inet_ntoa(in),
				rpy->time, rpy->dataLen, rpy->TTL);
		}
	}
}

void Controller::reSearch()
{
	//先停止所有线程
	if (t!=nullptr)
	{
		ctrlpm::stop = true;
		ctrlpm::isSearching = true;
		Sleep(1010);
		ctrlpm::cv.notify_all();
		auto thread_size = ctrlpm::IPRange / ctrlpm::range4Thread;
		for (size_t i = 0; i < thread_size; i++)
		{
			if (t[i].joinable())
			{
				t[i].join();
			}
		}
	}
	delete[]t;
	//再重新建立线程搜索。不停止不阻塞
	ctrlpm::stop = false;
	ctrlpm::isSearching = true;
	startSeaching();
}

void Controller::show()
{
	view->show();
}
