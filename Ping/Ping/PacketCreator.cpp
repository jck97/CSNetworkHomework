#include "PacketCreator.h"



PacketCreator::PacketCreator()
{
}


PacketCreator::~PacketCreator()
{
}

USHORT PacketCreator::checkSum(const USHORT * packet, int n)
{
	//1.把需校验的数据看成以16位为单位的数字组成，依次进行求和，并存到32位的整型中
	//2.把求和结果中的高16位(进位)加到低16位上，
	//3.如果还有进位，重复第2步[实际上，最多会执行2次]
	//4.将这个32位的整型按位取反，并强制转换为16位整型(截断)后返回
	unsigned int res = 0;
	for (size_t i = 0; i < n; i++)
	{
		res += packet[i];
	}
	res = (res >> 16) + (res & 0xffff);
	res = (res >> 16) + (res & 0xffff);
	return (USHORT)res;
}
