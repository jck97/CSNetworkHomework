#pragma once
#include <WinSock2.h>
#include <memory>
class PacketCreator
{
public:
	virtual void createPacket(char*destIP, char*data,int dataLen, char* packet,int& totalLen) = 0;
	PacketCreator();
	~PacketCreator();
protected:
	USHORT checkSum(const USHORT* packet,int n);
};

