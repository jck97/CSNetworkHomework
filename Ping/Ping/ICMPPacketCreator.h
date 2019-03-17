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
	ICMPPacketCreator();
	ICMPPacketCreator(int size);

	char* getPacket();
	PacketCreator* setPktSize(int size);
	PacketCreator* initPacket();
	PacketCreator* setSeq(USHORT seq);
	PacketCreator* setType(BYTE type);
	PacketCreator* setCode(BYTE code);
	PacketCreator* setId(USHORT id);
	PacketCreator* setData(const char *data, int len);
	~ICMPPacketCreator();
private:
	ICMPHead* icmpHead;
};

