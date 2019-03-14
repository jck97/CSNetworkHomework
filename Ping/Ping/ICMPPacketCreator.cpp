#include "ICMPPacketCreator.h"

USHORT ICMPPacketCreator::seq = 0;

ICMPPacketCreator::ICMPPacketCreator(BYTE _type):
	type(_type)
{
}

void ICMPPacketCreator::createPacket(char * destIP, char * data,int dataLen, char * packet, int& totalLen)
{
	totalLen = sizeof(icmpHead) + dataLen;
	packet = new char[totalLen];
	auto pIcmpHead = (icmpHead*)packet;
	pIcmpHead->type = type;
	pIcmpHead->code = 0;
	pIcmpHead->id  = (USHORT)GetCurrentProcessId();
	pIcmpHead->seqNum = ++seq;
	memcpy(packet+sizeof(icmpHead),data,dataLen);
	pIcmpHead->checkSum = checkSum((USHORT*)packet,totalLen/2);
}


ICMPPacketCreator::~ICMPPacketCreator()
{
}
