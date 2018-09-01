#pragma once

enum SocketInfo
{
	SOCK_TCP	= SOCK_STREAM, //1
	SOCK_UDP	= SOCK_DGRAM, //2
	SOCK_IPv4	= AF_INET, //2
	SOCK_IPv6	= AF_INET6, //23
};

class Winsock_base
{
private:
	WSADATA m_Wsa;
	
	int m_Family;
	struct sockaddr_in m_Sockinf;
	struct hostent *m_IpAddr;
	unsigned short m_Port;

public:
	SOCKET m_Sock;
	Winsock_base();
	bool CreateSocket(int af, int type, int protocol);
	bool Connect(char *pIpAddr, unsigned short Port);
	bool Send(const char *Buffer, int Bufferlen);
	int Recv(char *Buffer, int Bufferlen);
	~Winsock_base();
};