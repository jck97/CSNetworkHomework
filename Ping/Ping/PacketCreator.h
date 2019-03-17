#pragma once
#include <WinSock2.h>
#include <qdebug.h>
#include <memory>

class InitPacketFailExceptiom {
public:
	InitPacketFailExceptiom(QString _info) :
		info(_info) {
	}
	QString info;
};

class PacketCreator
{
public:
	virtual void initPacket(char*destIP,const char*data,
		int dataLen, char *&packet,int& totalLen) = 0;
	PacketCreator();
	~PacketCreator();
protected:
	USHORT checkSum(const USHORT* packet,int n);
private:
};

