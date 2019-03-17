#include "ICMPPacketCreator.h"

ICMPPacketCreator::ICMPPacketCreator()
{
}

ICMPPacketCreator::ICMPPacketCreator(int size)
{
	this->pktSize = size;
	this->packet = new char[size];
	this->icmpHead = (ICMPHead*)packet;
}

char * ICMPPacketCreator::getPacket()
{
	icmpHead->checkSum = 0;
	icmpHead->checkSum = this->checkSum((USHORT*)packet,pktSize);
	return packet;
}

PacketCreator * ICMPPacketCreator::setPktSize(int size)
{
	if (this->packet != nullptr) {
		icmpHead = nullptr;
		delete []packet;
	}
	this->pktSize = size;
	this->packet = new char[size];
	icmpHead = (ICMPHead*)packet;
	return this;
}

PacketCreator * ICMPPacketCreator::initPacket()
{
	PacketCreator* res = nullptr;
	if (pktSize > 0)
	{
		packet = new char[pktSize];
		icmpHead = (ICMPHead*)packet;
		res = this;
	}
	return res;
}

PacketCreator * ICMPPacketCreator::setSeq(USHORT seq)
{
	icmpHead->seqNum = seq;
	return this;
}

PacketCreator * ICMPPacketCreator::setType(BYTE type)
{
	icmpHead->type = type;
	return this;
}

PacketCreator * ICMPPacketCreator::setCode(BYTE code)
{
	icmpHead->code = code;
	return this;
}

PacketCreator * ICMPPacketCreator::setId(USHORT id)
{
	icmpHead->id = id;
	return this;
}

PacketCreator * ICMPPacketCreator::setData(const char * data, int len)
{
	memcpy(packet + sizeof(ICMPHead), data, len);
	return this;
}

ICMPPacketCreator::~ICMPPacketCreator()
{
	icmpHead = nullptr;
}
