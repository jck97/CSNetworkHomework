#pragma once
#include <WinSock2.h>
#include <iostream>
#include <memory>
#include <ICMPPacketCreator.h>

typedef struct
{//不包含可选部分
#ifdef RTP_BIG_ENDIAN
	BYTE version : 4;        //数据报的IP版本
	BYTE IHL : 4;            //ip首部长度
	BYTE TOS;                //服务类型
	USHORT  ToltalLen;       //数据报长度
	USHORT  id;              //标识。长数据分组发送时用到
	USHORT  flag : 3;        //分片相关数据位
	USHORT  fragOffset : 13; //片偏移，分片相关
#else
	BYTE IHL : 4;
	BYTE version : 4;
	BYTE TOS; 
	USHORT  ToltalLen; 
	USHORT  id;
	USHORT  fragOffset : 13; 
	USHORT  flag : 3;
#endif
	BYTE TTL;                //寿命。time to live
	BYTE protocol;           //指定运输协议
	USHORT checkSum;         //校验和。用于数据校验
	ULONG srcIP;             //源id
	ULONG dstIP;             //目标id
}IPHead;

typedef struct
{
	DWORD time;//往返时间
	DWORD dataLen;//接收数据长度
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
