#include "ICMPPacketCreator.h"

ICMPPacketCreator::ICMPPacketCreator(int size)
	:PacketCreator(size)
{
	this->packet = new char[size];
	this->icmpHead = (ICMPHead*)packet;
}

char * ICMPPacketCreator::getPacket()
{
	icmpHead->checkSum = check_sum(packet, pktSize);
	qDebug() << "check sum:" << icmpHead->checkSum;
	return packet;
}

ICMPPacketCreator::~ICMPPacketCreator()
{
	icmpHead = nullptr;
}
