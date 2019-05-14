#include "PacketCreator.h"

USHORT check_sum(const char * chars, int n)
{
	//1.����У������ݿ�����16λΪ��λ��������ɣ����ν�����ͣ����浽32λ��������
	//2.����ͽ���еĸ�16λ(��λ)�ӵ���16λ�ϣ�
	//3.������н�λ���ظ���2��[ʵ���ϣ�����ִ��2��]
	//4.�����32λ�����Ͱ�λȡ������ǿ��ת��Ϊ16λ����(�ض�)�󷵻�
	unsigned int cksum = 0;
	auto nums = (const USHORT *)(chars);

	while (n > 1) {
		cksum += *nums;
		nums++;
		n -= sizeof(USHORT);
	}

	if (n == 1) {
		cksum += *(UCHAR*)nums;
	}

	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return ~cksum;
}

