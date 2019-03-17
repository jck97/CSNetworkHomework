#include "PacketCreator.h"

PacketCreator::PacketCreator()
{
	this->pktSize = -1;
}

PacketCreator * PacketCreator::setPktSize(int size)
{
	this->pktSize = size; 
	return nullptr;
}

PacketCreator * PacketCreator::initPacket()
{
	PacketCreator* res = nullptr;
	if (pktSize > 0)
	{
		packet = new char[pktSize];
		res = this;
	}
	return res;
}
USHORT PacketCreator::checkSum(const USHORT * buffer, int size)
{
	//1.把需校验的数据看成以16位为单位的数字组成，依次进行求和，并存到32位的整型中
	//2.把求和结果中的高16位(进位)加到低16位上，
	//3.如果还有进位，重复第2步[实际上，最多会执行2次]
	//4.将这个32位的整型按位取反，并强制转换为16位整型(截断)后返回
	unsigned long cksum = 0;

	while (size > 1) {
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}

	if (size) {
		cksum += *(UCHAR*)buffer;
	}

	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return (USHORT)(~cksum);
}

PacketCreator::~PacketCreator()
{
	if (packet != nullptr)
		delete []packet;
}

