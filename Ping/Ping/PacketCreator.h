#pragma once
#include <WinSock2.h>
#include <qdebug.h>
#include <memory>
//
//
#define DTPCOP qDebug() << "undefined fuction!";\
			   assert(0);return nullptr;
class PacketCreator
{
public:
	PacketCreator();
	int inline getPktSize() { return pktSize; }
	virtual char* getPacket() { return packet; }
	
	virtual PacketCreator* setPktSize(int size);
	virtual PacketCreator*  initPacket();

//************* ICMP ************************************************************
	virtual PacketCreator* setSeq(USHORT seq) { DTPCOP };
	virtual PacketCreator* setType(BYTE type) { DTPCOP };
	virtual PacketCreator* setCode(BYTE code) { DTPCOP };
	virtual PacketCreator* setId(USHORT id) { DTPCOP };
	virtual PacketCreator* setData(const char *data, int len) { DTPCOP };
//************ end ICMP ********************************************************


/***method of some other protocol
to add other protocol serporrt,
add some functions,or override some functions;
************************************/

	~PacketCreator();
protected:
	USHORT checkSum(const USHORT* packet,int n);
	char* packet;
	int pktSize;
private:
};

class InitPacketFailExceptiom {
public:
	InitPacketFailExceptiom(QString _info) :
		info(_info) {
	}
	QString info;
};