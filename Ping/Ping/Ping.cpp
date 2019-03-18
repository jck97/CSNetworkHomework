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

	//�� wVersionRequested��һ��WORD��˫�ֽڣ�����ֵ��
	//����߰汾��Windows Sockets֧�ֵ�����ʹ�ã�
	//�߽��ֽ�ָ��С�汾(�޶���)��, ��λ�ֽ�ָ�����汾�š�
	//��lpWSAData ָ��WSADATA���ݽṹ��ָ�룬
	//��������Windows Socketsʵ�ֵ�ϸ�ڡ�
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		qDebug() << "WSAStartup failed"<< endl;
		throw InitFailException(QString((LONG)GetLastError()));
	}

	//SOCKET WSASocket(int af,int type,int protocol,LPWSAPROTOCOL_INFO lpProtocolInfo,
	//	GROUP g,DWORD dwFlags);�书�ܶ��Ǵ���һ��ԭʼ�׽��֡�
	//af��[in]һ����ַ��淶��Ŀǰ��֧��AF_INET��ʽ���༴ARPA Internet��ַ��ʽ��
	//type�����׽ӿڵ�����������
	//protocol���׽ӿ�ʹ�õ��ض�Э�飬��������߲�Ըָ��Э����Ϊ0��
	//lpProtocolInfo��һ��ָ��PROTOCOL_INFO�ṹ��ָ�룬�ýṹ�����������׽ӿڵ����ԡ�
	//����������ǿգ���ǰ����������af, type, protocol�������ԡ�
	//g��������δ��ʹ�õ��׽����顣�׽ӿ���ı�ʶ����
	//iFlags���׽ӿ�����������
	//@return:���޴�������WSASocket()�������׽ӿڵ������֡�
	//����Ļ������� INVALID_SOCKET��Ӧ�ó���ɶ�����WSAGetLastError()����ȡ��Ӧ�Ĵ�����롣
	this->sockRaw = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, 0);
	//this->sockRaw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (this->sockRaw == INVALID_SOCKET)
	{
		qDebug() << "create socket failed" << endl;
		throw InitFailException(QString(WSAGetLastError()));
	}
	int bread = 0;

#if 0		//���ֻ�������Ҫ���´���
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

	//��socket���¼�������ע�ᵽϵͳ������socket���óɷ�����ģʽ��
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
	//����socket
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
			this->reply->time = (DWORD)((clock() - startClock) * 1000 / CLOCKS_PER_SEC);//����ʱ��
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
		this->reply->time = (DWORD)((clock() - startClock) * 1000 / CLOCKS_PER_SEC);//����ʱ��
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
	//s �׽���
	//buff ���������ݵĻ�����
	//size ����������
	//Flags ���÷�ʽ��־λ, һ��Ϊ0, �ı�Flags������ı�Sendto���͵���ʽ
	//addr ����ѡ��ָ�룬ָ��Ŀ���׽��ֵĵ�ַ
	//addrLen ��ַ�ĳ���
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
				if (icmpHead->id == this->CurrentProcID      //�ǵ�ǰ���̷����ı���
					&& icmpHead->seqNum == this->seq         //�Ǳ��������ĵ���Ӧ����
					&& icmpHead->type == ping::ECHO_REPLY)  //��ICMP��Ӧ����
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
