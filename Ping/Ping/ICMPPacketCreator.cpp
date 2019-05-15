#include "ICMPPacketCreator.h"

ICMPPacketCreator::ICMPPacketCreator(int size)
	:PacketCreator(size)
{
	this->packet = new char[size];
	this->icmpHead = (ICMPHead*)packet;
}

char * ICMPPacketCreator::getPacket()
{
	//计算校验和之前，必须把相应的位置置为0.
	icmpHead->checkSum = 0;
	icmpHead->checkSum = check_sum(packet, pktSize);
	return packet;
}

ICMPPacketCreator::~ICMPPacketCreator()
{
	icmpHead = nullptr;
}
