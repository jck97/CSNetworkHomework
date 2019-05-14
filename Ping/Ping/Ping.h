#pragma once
#include <WinSock2.h>
#include <iostream>
#include <memory>
#include <ICMPPacketCreator.h>

typedef struct
{//��������ѡ����
#ifdef RTP_BIG_ENDIAN
	BYTE version : 4;        //���ݱ���IP�汾
	BYTE IHL : 4;            //ip�ײ�����
	BYTE TOS;                //��������
	USHORT  ToltalLen;       //���ݱ�����
	USHORT  id;              //��ʶ�������ݷ��鷢��ʱ�õ�
	USHORT  flag : 3;        //��Ƭ�������λ
	USHORT  fragOffset : 13; //Ƭƫ�ƣ���Ƭ���
#else
	BYTE IHL : 4;
	BYTE version : 4;
	BYTE TOS; 
	USHORT  ToltalLen; 
	USHORT  id;
	USHORT  fragOffset : 13; 
	USHORT  flag : 3;
#endif
	BYTE TTL;                //������time to live
	BYTE protocol;           //ָ������Э��
	USHORT checkSum;         //У��͡���������У��
	ULONG srcIP;             //Դid
	ULONG dstIP;             //Ŀ��id
}IPHead;

typedef struct
{
	DWORD time;//����ʱ��
	DWORD dataLen;//�������ݳ���
	DWORD TTL; //ttl
	void print() {
		qDebug() << "cost time:" << time << "ms  data length:" << dataLen << "Byte  TTL:" << TTL;
	}
}PingReply;

class InitFailException {
public:
	InitFailException(QString _info) :
		info(_info) {
	};
	QString info;
};

class Ping
{
public:
	Ping();
	void ping(char *destIP, int count);
	void ping(DWORD destIP,int count);
	bool isReach(char *destIP);
	bool isReach(DWORD destIP);
	BOOL sendICMP(struct sockaddr* destaddr, int addrSize);
	BOOL recvPacket(struct sockaddr* destaddr, int addrSize);
	const std::shared_ptr<PingReply>& getReply() {
		return reply;
	};
	~Ping();

private:
	SOCKET sockRaw;
	WSAEVENT event;
	std::unique_ptr< PacketCreator<ICMPPacketCreator> > pktCreator;
	std::shared_ptr<PingReply> reply;
	static USHORT seq;
	USHORT CurrentProcID;
	int icmpLen;

	void init_socket();
	void init_packet();
};
