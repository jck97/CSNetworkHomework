#pragma once
#include "PacketCreator.h"

typedef struct
{
	BYTE type;               //type��codeһ�����icmp�������ͣ�����ͻ�Ӧ�ֱ�Ϊ8��0
	BYTE code;               //ping�����С�codeΪ0
	USHORT checkSum;         //У���
	USHORT id;               //��ʶ�������һ�����뱾���̵ı�ʶ����
	USHORT seqNum;           //���
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

