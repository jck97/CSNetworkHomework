#pragma once
#include <WinSock2.h>
#include <memory>
using std::shared_ptr;

constexpr auto DATASIZE = 32;
constexpr auto DATA = "abcdefghijklmnopqrstuvwabcdefghi";
constexpr auto ECHO_REQUEST = 8;
constexpr auto ECHO_REPLY = 0;

typedef struct 
{//��������ѡ����
	BYTE version : 4;        //���ݱ���IP�汾
	BYTE IHL : 4;            //ip�ײ�����
	BYTE TOS;                //��������
	USHORT  ToltalLen;       //���ݱ�����
	USHORT  id;              //��ʶ�������ݷ��鷢��ʱ�õ�
	USHORT  flag : 3;        //��Ƭ�������λ
	USHORT  fragOffset : 13; //Ƭƫ�ƣ���Ƭ���
	BYTE TTL;                //������time to live
	BYTE protocol;           //ָ������Э��
	USHORT checkSum;         //У��͡���������У��
	ULONG srcIP;             //Դid
	ULONG dstIP;             //Ŀ��id
}IPHead;

typedef struct
{
	DWORD time;//����ʱ��
	DWORD Byte;//�������ݳ���
	DWORD TTL; //ttl
}PingReply;

class Ping
{
public:
	Ping(char*destIP,PingReply& reply);

	shared_ptr<PingReply> getReply() {
		return reply;
	};
	~Ping();
private:
	shared_ptr<PingReply> reply;
};

