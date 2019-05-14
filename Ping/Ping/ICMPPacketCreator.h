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
	BYTE type;               //type��codeһ�����icmp�������ͣ�����ͻ�Ӧ�ֱ�Ϊ8��0
	BYTE code;               //ping�����С�codeΪ0
	USHORT checkSum;         //У���
	USHORT id;               //��ʶ�������һ�����뱾���̵ı�ʶ����
	USHORT seqNum;           //���
};

class ICMPPacketCreator :
	public PacketCreator<ICMPPacketCreator>
{
public:
	ICMPPacketCreator(int size);
	char* getPacket()override;

	//����ģ��,��Ӧ�õ��øú���
	template<typename T>
	void setProperty(T property)
	{
		qDebug() << "��Ӧ�ó��ֵ���ICMPPacketCreator ����ģ\
		�庯��setProperty������setPropertyͬ�������Ĳ���Ӧ��Ϊicmp_xx..." << endl;
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

	//�Բ�ͬ�����Խ���ģ���ػ�
	template<> void setProperty(icmp_type type);
	template<> void setProperty(icmp_code code);
	template<> void setProperty(icmp_id id);
	template<> void setProperty(icmp_seq seq);
	template<> void setProperty(icmp_size size);
	template<> void setProperty(icmp_data data);

	~ICMPPacketCreator();
private:
	//ֻʹ�ñ�ʶ
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
