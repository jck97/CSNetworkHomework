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
	//1.����У������ݿ�����16λΪ��λ��������ɣ����ν�����ͣ����浽32λ��������
	//2.����ͽ���еĸ�16λ(��λ)�ӵ���16λ�ϣ�
	//3.������н�λ���ظ���2��[ʵ���ϣ�����ִ��2��]
	//4.�����32λ�����Ͱ�λȡ������ǿ��ת��Ϊ16λ����(�ض�)�󷵻�
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

