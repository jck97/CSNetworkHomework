#include "Ping.h"
USHORT Ping::seq = 0;
#define ublock false;
namespace ping {
	constexpr auto DATASIZE = 32;
	constexpr auto DATA = "abcdefghijklmnopqrstuvwabcdefghi";
	constexpr auto ECHO_REQUEST = 8;
	constexpr auto ECHO_REPLY = 0;
	constexpr auto TIMEOUT = 1000;
	constexpr auto MAXPACKETLEN = 256;
	constexpr auto PORT = 25011;
}

Ping::Ping() :
	icmpLen(sizeof(ICMPHead)+ping::DATASIZE)
{
	this->reply = std::make_shared<PingReply>();
	this->pktCreator = std::make_unique<ICMPPacketCreator>(icmpLen);
	init_socket();
	init_packet();
}

void Ping::init_socket() throw(InitFailException)
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
	//this->sockRaw = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, 0);

	this->sockRaw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (this->sockRaw == INVALID_SOCKET)
	{
		qDebug() << "create socket failed" << endl;
		throw InitFailException(QString(WSAGetLastError()));
	}
	int bread = 0;

#if 1		//部分机器上需要以下代码
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

void Ping::init_packet()
{
	pktCreator->setProperty(
		icmp_size{ sizeof(ICMPHead) + ping::DATASIZE },
		icmp_code{ ping::ECHO_REQUEST },
		icmp_data{ ping::DATA,ping::DATASIZE },
		icmp_type{ ping::ECHO_REQUEST }
	);
}

void Ping::ping(char * destIP,int count = 4)
{
	ping(inet_addr(destIP),count);
}

void Ping::ping(DWORD destIP,int count = 4)
{

	while (count--) {
		if (isReach(destIP))
		{
			reply->print();
		}
		else
		{
			qDebug() << "time out" << endl;
		}
		Sleep(100);
	}
}

bool Ping::isReach(char * destIP)
{
	return isReach(inet_addr(destIP));
}

bool Ping::isReach(DWORD destIP)
{
	bool res = false;
	sockaddr_in addr_in;
	int addrSize = sizeof(addr_in);
	memset(&addr_in, 0, addrSize);
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(ping::PORT);
	addr_in.sin_addr.s_addr = destIP;

	this->CurrentProcID = (USHORT)GetCurrentProcessId();
	pktCreator->setProperty(
		icmp_id{ (USHORT)CurrentProcID },
		icmp_seq{ ++seq }
	);

	LONGLONG startClock = clock();
	BOOL sendSucc = sendICMP((sockaddr*)&addr_in, addrSize);
	if (sendSucc)
	{
		res = (bool)recvPacket((sockaddr*)&addr_in, addrSize);
		this->reply->time = (DWORD)((clock() - startClock) * 1000 / CLOCKS_PER_SEC);//毫秒时间
	}
	else
	{
		qDebug() << "send failed" << endl;
	}
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

	char* data = pktCreator->getPacket();
	int bread = sendto(this->sockRaw, data, 
		this->icmpLen,0, destaddr, addrSize);
	if (bread == SOCKET_ERROR)
	{
		if (bread == WSAETIMEDOUT) {
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
#if ublock
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
					qDebug() << "time out in thread:" << GetCurrentThreadId();
					return res;
				}
				qDebug() << "revefrom() failed id:" << WSAGetLastError() << endl;
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
#if ublock
		}
	}
#endif
	return res;
}

Ping::~Ping()
{
	closesocket(sockRaw);
	WSACleanup();
}
