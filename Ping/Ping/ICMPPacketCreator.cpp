#include "ICMPPacketCreator.h"

ICMPPacketCreator::ICMPPacketCreator(int size)
	:PacketCreator(size)
{
	this->packet = new char[size];
	this->icmpHead = (ICMPHead*)packet;
}

char * ICMPPacketCreator::getPacket()
{
	//����У���֮ǰ���������Ӧ��λ����Ϊ0.
	icmpHead->checkSum = 0;
	icmpHead->checkSum = check_sum(packet, pktSize);
	return packet;
}

ICMPPacketCreator::~ICMPPacketCreator()
{
	icmpHead = nullptr;
}
