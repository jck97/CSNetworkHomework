#pragma once
#include "PacketCreator.h"

constexpr auto DATASIZE = 32;
constexpr auto DATA = "abcdefghijklmnopqrstuvwabcdefghi";
typedef struct
{
	BYTE type;               //type��codeһ�����icmp�������ͣ�����ͻ�Ӧ�ֱ�Ϊ8��0
	BYTE code;               //ping�����С�codeΪ0
	USHORT checkSum;         //У���
	USHORT id;               //��ʶ�������һ�����뱾���̵ı�ʶ����
	USHORT seqNum;           //���
}icmpHead;

class ICMPPacketCreator :
	public PacketCreator
{
public:
	ICMPPacketCreator(BYTE type);
	void createPacket(char*destIP, char*data,int dataLen, char* packet, int& totalLen);
	~ICMPPacketCreator();
private:
	BYTE type;
};

