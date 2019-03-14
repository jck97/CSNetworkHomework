#pragma once
#include <WinSock2.h>
#include <memory>
using std::shared_ptr;

constexpr auto DATASIZE = 32;
constexpr auto DATA = "abcdefghijklmnopqrstuvwabcdefghi";
constexpr auto ECHO_REQUEST = 8;
constexpr auto ECHO_REPLY = 0;

typedef struct 
{//不包含可选部分
	BYTE version : 4;        //数据报的IP版本
	BYTE IHL : 4;            //ip首部长度
	BYTE TOS;                //服务类型
	USHORT  ToltalLen;       //数据报长度
	USHORT  id;              //标识。长数据分组发送时用到
	USHORT  flag : 3;        //分片相关数据位
	USHORT  fragOffset : 13; //片偏移，分片相关
	BYTE TTL;                //寿命。time to live
	BYTE protocol;           //指定运输协议
	USHORT checkSum;         //校验和。用于数据校验
	ULONG srcIP;             //源id
	ULONG dstIP;             //目标id
}IPHead;

typedef struct
{
	DWORD time;//往返时间
	DWORD Byte;//接受数据长度
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

