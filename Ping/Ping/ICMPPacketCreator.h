#pragma once
#include "PacketCreator.h"

using icmp_type = struct { BYTE type; };
using icmp_code = struct { BYTE code; };
using icmp_id   = struct { USHORT id; };
using icmp_seq  = struct { USHORT seq; };
using icmp_size = struct { int size; };
using icmp_data = struct { const char *data; int len; };
using ICMPHead  = struct
{
	BYTE type;               //type与code一起决定icmp报文类型，请求和回应分别为8，0
	BYTE code;               //ping报文中。code为0
	USHORT checkSum;         //校验和
	USHORT id;               //标识符，这个一般填入本进程的标识符。
	USHORT seqNum;           //序号
};

class ICMPPacketCreator :
	public PacketCreator<ICMPPacketCreator>
{
public:
	ICMPPacketCreator(int size);
	char* getPacket()override;

	//泛化模板,不应该调用该函数
	template<typename T>
	void setProperty(T property)
	{
		qDebug() << "不应该出现调用ICMPPacketCreator 泛化模\
		板函数setProperty。调用setProperty同名函数的参数应该为icmp_xx..." << endl;
		//logging .....
		exit(-1);
	};

	void initPacket() override
	{
		if (pktSize > 0)
		{
			if (packet != nullptr)
			{
				delete[] packet;
			}
			packet = new char[pktSize];
		}
	};

	//对不同的属性进行模板特化
	template<> void setProperty(icmp_type type);
	template<> void setProperty(icmp_code code);
	template<> void setProperty(icmp_id id);
	template<> void setProperty(icmp_seq seq);
	template<> void setProperty(icmp_size size);
	template<> void setProperty(icmp_data data);

	~ICMPPacketCreator();
private:
	//只使用标识
	ICMPHead* icmpHead;
};

template<>
inline void ICMPPacketCreator::setProperty(icmp_type type)
{
	icmpHead->type = type.type;
}

template<>
inline void ICMPPacketCreator::setProperty(icmp_code code)
{
	icmpHead->code = code.code;
}

template<>
inline void ICMPPacketCreator::setProperty(icmp_id id)
{
	icmpHead->id = id.id;
}

template<>
inline void ICMPPacketCreator::setProperty(icmp_seq seq)
{
	icmpHead->seqNum = seq.seq;
}

template<>
inline void ICMPPacketCreator::setProperty(icmp_size s)
{
	int size = s.size;
	if (this->packet != nullptr) {
		icmpHead = nullptr;
		delete[]packet;
	}
	this->pktSize = size;
	this->packet = new char[size];
	icmpHead = (ICMPHead*)packet;
}

template<>
inline void ICMPPacketCreator::setProperty(icmp_data data)
{
	memcpy(packet + sizeof(ICMPHead), data.data, data.len);
}
