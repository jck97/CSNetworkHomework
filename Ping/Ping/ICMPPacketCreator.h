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
	ICMPPacketCreator(BYTE type);
	void initPacket(char*destIP,const char*data,
		int dataLen, char *&packet, int& totalLen);
	~ICMPPacketCreator();
protected:
	BYTE type;
};

