#pragma once
#include "PacketCreator.h"

typedef struct
{
	BYTE type;               //type与code一起决定icmp报文类型，请求和回应分别为8，0
	BYTE code;               //ping报文中。code为0
	USHORT checkSum;         //校验和
	USHORT id;               //标识符，这个一般填入本进程的标识符。
	USHORT seqNum;           //序号
}ICMPHead;

class ICMPPacketCreator :
	public PacketCreator
{
public:
	ICMPPacketCreator(BYTE type);
	void initPacket(char*destIP,const char*data,
		int dataLen, char *&packet, int& totalLen);
	~ICMPPacketCreator();
protected:
	BYTE type;
};

