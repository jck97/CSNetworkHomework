#include "Ping.h"
USHORT Ping::seq = 0;
#define block false;
Ping::Ping() :
	icmpLen(sizeof(ICMPHead)+ping::DATASIZE)
{
	this->reply = std::make_shared<PingReply>();
	this->pktCreator = std::make_shared<ICMPPacketCreator>(icmpLen);
}

void Ping::init() throw(InitFailException)
{
	WSADATA wsaData;
	int optVal = ping::TIMEOUT;

	//⑴ wVersionRequested：一个WORD（双字节）型数值，
	//在最高版本的Windows Sockets支持调用者使用，
	//高阶字节指定小版本(修订本)号, 低位字节指定主版本号。
	//⑵lpWSAData 指向WSADATA数据结构的指针，
	//用来接收Windows Sockets实现的细节。
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		qDebug() << "WSAStartup failed"<< endl;
		throw InitFailException(QString((LONG)GetLastError()));
	}

	//SOCKET WSASocket(int af,int type,int protocol,LPWSAPROTOCOL_INFO lpProtocolInfo,
	//	GROUP g,DWORD dwFlags);其功能都是创建一个原始套接字。
	//af：[in]一个地址族规范。目前仅支持AF_INET格式，亦即ARPA Internet地址格式。
	//type：新套接口的类型描述。
	//protocol：套接口使用的特定协议，如果调用者不愿指定协议则定为0。
	//lpProtocolInfo：一个指向PROTOCOL_INFO结构的指针，该结构定义所创建套接口的特性。
	//如果本参数非空，则前三个参数（af, type, protocol）被忽略。
	//g：保留给未来使用的套接字组。套接口组的标识符。
	//iFlags：套接口属性描述。
	//@return:若无错误发生，WSASocket()返回新套接口的描述字。
	//否则的话，返回 INVALID_SOCKET，应用程序可定调用WSAGetLastError()来获取相应的错误代码。
	this->sockRaw = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, 0);
	//this->sockRaw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (this->sockRaw == INVALID_SOCKET)
	{
		qDebug() << "create socket failed" << endl;
		throw InitFailException(QString(WSAGetLastError()));
	}
	int bread = 0;

#if 0		//部分机器上需要以下代码
	optVal = 1;
	bread = setsockopt(sockRaw, SOL_SOCKET, SO_EXCLUSIVEADDRUSE,
		(char *)&optVal, sizeof(optVal));
	if (bread == SOCKET_ERROR) {
		qDebug() << "set exclusive addr use failed" << endl;
		throw InitFailException(QString(WSAGetLastError()));
	}

	bread = setsockopt(sockRaw, SOL_SOCKET, SO_BROADCAST,
		(char *)&optVal, sizeof(optVal));
	if (bread == SOCKET_ERROR) {
		qDebug() << "set broadcase failed" << endl;
		throw InitFailException(QString(WSAGetLastError()));
	}
#endif

	optVal = ping::TIMEOUT;
	bread = setsockopt(this->sockRaw, SOL_SOCKET, 
		SO_RCVTIMEO, (char*) &optVal, sizeof(optVal));
	if (bread == SOCKET_ERROR)
	{
		qDebug() << "set receive timeout failed" << endl;
		throw InitFailException(QString(WSAGetLastError()));
	}

	optVal = ping::TIMEOUT;
	bread = setsockopt(this->sockRaw, SOL_SOCKET,
		SO_SNDTIMEO, (char*) & optVal, sizeof(optVal));
	if (bread == SOCKET_ERROR) {
		qDebug() << "set send time out failed" << endl;
		throw InitFailException(QString(WSAGetLastError()));
	}

	//将socket和事件关联并注册到系统，并将socket设置成非阻塞模式。
#if block
	WSAEventSelect(this->sockRaw, this->event, FD_READ);
#endif
}

void Ping::ping(char * destIP,int count = 4)
{
	//qDebug() << inet_addr(destIP);
	ping(inet_addr(destIP),count);
}

void Ping::ping(DWORD destIP,int count = 4)
{
	//配置socket
	init();
	sockaddr_in dest;
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = destIP;
	int addrSize = sizeof(dest);
	CurrentProcID = GetCurrentProcessId();

	pktCreator
		->setPktSize(sizeof(ICMPHead) + ping::DATASIZE)
		->setCode(ping::ECHO_REQUEST)
		->setData(ping::DATA, ping::DATASIZE)
		->setId(CurrentProcID)
		->setType(ping::ECHO_REQUEST)
		->getPacket();

	while (count--) {
		LONGLONG startClock = clock();
		pktCreator->setSeq(++seq);
		BOOL sendSucc = sendICMP((sockaddr*)&dest, addrSize);
		if (sendSucc)
		{
			recvPacket((sockaddr*)&dest, addrSize);
			this->reply->time = (DWORD)((clock() - startClock) * 1000 / CLOCKS_PER_SEC);//毫秒时间
			this->reply->print();
		}
		else
		{
			qDebug() << "send failed" << endl;
			continue;
		}
		Sleep(1000);
	}
	closesocket(sockRaw);
	WSACleanup();
}

bool Ping::isReach(char * destIP)
{
	return isReach(inet_addr(destIP));
}

bool Ping::isReach(DWORD destIP)
{
	bool res = false;
	init();
	sockaddr_in dest;
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = destIP;
	int addrSize = sizeof(dest);
	CurrentProcID = GetCurrentProcessId();

	pktCreator
		->setPktSize(sizeof(ICMPHead) + ping::DATASIZE)
		->setCode(ping::ECHO_REQUEST)
		->setData(ping::DATA, ping::DATASIZE)
		->setId(CurrentProcID)
		->setType(ping::ECHO_REQUEST)
		->getPacket();

	LONGLONG startClock = clock();
	pktCreator->setSeq(++seq);
	BOOL sendSucc = sendICMP((sockaddr*)&dest, addrSize);
	if (sendSucc)
	{
		res = (bool)recvPacket((sockaddr*)&dest, addrSize);
		this->reply->time = (DWORD)((clock() - startClock) * 1000 / CLOCKS_PER_SEC);//毫秒时间
	}
	else
	{
		qDebug() << "send failed" << endl;
	}
	closesocket(sockRaw);
	WSACleanup();
	return res;
}

BOOL Ping::sendICMP(sockaddr * destaddr, int addrSize)
{
	BOOL res = TRUE;
	//typedef int(_stdcall * SendTo) (SOCKET s,
	//	const char * buff,
	//	DWORD size,
	//	int Flags,
	//	const sockaddr * addr,
	//	int addrLen);
	//s 套接字
	//buff 待发送数据的缓冲区
	//size 缓冲区长度
	//Flags 调用方式标志位, 一般为0, 改变Flags，将会改变Sendto发送的形式
	//addr （可选）指针，指向目的套接字的地址
	//addrLen 地址的长度
	this->CurrentProcID = GetCurrentProcessId();
	char* data = pktCreator->getPacket();
	int bread = sendto(this->sockRaw, data, 
		this->icmpLen,0, destaddr, addrSize);
	if (bread == SOCKET_ERROR)
	{
		if (bread == WSAETIMEDOUT) {
			//TODO();
			qDebug() << "time out"  << endl;
		}
		qDebug()<<" error code : " << WSAGetLastError() << endl;
		res = FALSE;
	}
	return res;
}

BOOL Ping::recvPacket(sockaddr * from, int fromlen)
{
	BOOL res = TRUE;
	char recvbuf[ping::MAXPACKETLEN];
	int timeout = ping::TIMEOUT;
#if block
	if (WSAWaitForMultipleEvents(1, &event, FALSE, timeout, FALSE) != WSA_WAIT_TIMEOUT) 
	{
		WSANETWORKEVENTS netEvent;
		WSAEnumNetworkEvents(this->sockRaw, this->event, &netEvent);
		if (netEvent.lNetworkEvents & FD_READ) {
#endif
			int recvLen = recvfrom(sockRaw, recvbuf, ping::MAXPACKETLEN,
				0, (struct sockaddr*)&from, &fromlen);
			if (recvLen == SOCKET_ERROR)
			{
				res = FALSE;
				if (WSAGetLastError() == WSAETIMEDOUT)
				{
					qDebug() << "time out" << endl;
					return res;
				}
				qDebug() << "revefrom() failed:" << WSAGetLastError() << endl;
			}
			else
			{
				IPHead *ipHead = (IPHead*)recvbuf;
				USHORT ipHeadLen = (USHORT)(ipHead->IHL) * 4;
				ICMPHead *icmpHead = (ICMPHead*)(recvbuf + ipHeadLen);
				if (icmpHead->id == this->CurrentProcID      //是当前进程发出的报文
					&& icmpHead->seqNum == this->seq         //是本次请求报文的响应报文
					&& icmpHead->type == ping::ECHO_REPLY)  //是ICMP响应报文
				{
					reply->dataLen = recvLen - sizeof(IPHead) - sizeof(ICMPHead);
					reply->TTL = ipHead->TTL;
				}
			}
#if block
		}
	}
#endif
	return res;
}

Ping::~Ping()
{
}
