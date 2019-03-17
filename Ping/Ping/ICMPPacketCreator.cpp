#include "ICMPPacketCreator.h"

ICMPPacketCreator::ICMPPacketCreator(BYTE _type):
	type(_type)
{
}

void ICMPPacketCreator::initPacket(
	char * destIP,const char * data,int dataLen, 
	char *&packet, int& totalLen)
	throw(InitPacketFailExceptiom)
{
	if (totalLen!= sizeof(ICMPHead) + dataLen || packet == nullptr)
	{
		totalLen = sizeof(ICMPHead) + dataLen;
		packet = new char[totalLen];
	}

	if (packet == nullptr)
	{
		qDebug() << "±¨ÎÄ¿Õ¼äÉêÇëÊ§°Ü£¡" << endl;
		throw InitPacketFailExceptiom(QString("±¨ÎÄ¿Õ¼äÉêÇëÊ§°Ü£¡"));
	}
	auto pIcmpHead = (ICMPHead*)packet;
	pIcmpHead->type = type;
	pIcmpHead->code = 0;
	pIcmpHead->id  = (USHORT)GetCurrentProcessId();
	memcpy(packet+sizeof(ICMPHead),data,dataLen);
	pIcmpHead->checkSum = 0;
	pIcmpHead->checkSum = checkSum((USHORT*)packet,totalLen/2);
}

ICMPPacketCreator::~ICMPPacketCreator()
{
}
