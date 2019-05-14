#pragma once
#include <WinSock2.h>
#include <qdebug.h>
#include <memory>
//
//
#define DTPCOP qDebug() << "undefined fuction!";\
			   assert(0);return nullptr;

template<typename childType>
class PacketCreator
{
public:
	explicit PacketCreator(int s) 
		:pktSize(s)
	{};

	int getPktSize()const { return pktSize; }
	virtual char* getPacket() { return packet; }
	
	virtual void setPktSize(int s)
	{
		this->pktSize = s;
	};

	virtual void initPacket()
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

	template<typename T>
	void setProperty(T&& ppy)
	{
		static_cast<childType*>(this)->setProperty(std::forward<T>(ppy));
	}

	template<typename T,typename... Args>
	void setProperty(T&& ppy,Args&&... res_ppy)
	{
		static_cast<childType*>(this)->setProperty(std::forward<T>(ppy));
		this->setProperty(std::forward<Args>(res_ppy)...);
	}

	virtual ~PacketCreator()
	{
		if (packet != nullptr)
			delete[] packet;
	};

protected:
	char* packet;
	int pktSize;
};

class InitPacketFailExceptiom {
public:
	InitPacketFailExceptiom(QString _info) :
		info(_info) {
	}
	QString info;
};

USHORT check_sum(const char *chars, int n);
