#include "PacketCreator.h"

USHORT check_sum(const char * chars, int n)
{
	//1.把需校验的数据看成以16位为单位的数字组成，依次进行求和，并存到32位的整型中
	//2.把求和结果中的高16位(进位)加到低16位上，
	//3.如果还有进位，重复第2步[实际上，最多会执行2次]
	//4.将这个32位的整型按位取反，并强制转换为16位整型(截断)后返回
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

