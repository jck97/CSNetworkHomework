#include "PacketCreator.h"



PacketCreator::PacketCreator()
{
}


PacketCreator::~PacketCreator()
{
}

USHORT PacketCreator::checkSum(const USHORT * packet, int n)
{
	//1.����У������ݿ�����16λΪ��λ��������ɣ����ν�����ͣ����浽32λ��������
	//2.����ͽ���еĸ�16λ(��λ)�ӵ���16λ�ϣ�
	//3.������н�λ���ظ���2��[ʵ���ϣ�����ִ��2��]
	//4.�����32λ�����Ͱ�λȡ������ǿ��ת��Ϊ16λ����(�ض�)�󷵻�
	unsigned int res = 0;
	for (size_t i = 0; i < n; i++)
	{
		res += packet[i];
	}
	res = (res >> 16) + (res & 0xffff);
	res = (res >> 16) + (res & 0xffff);
	return (USHORT)res;
}
