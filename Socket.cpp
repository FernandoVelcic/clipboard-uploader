#include "stdafx.h"
#include "Socket.h"

Winsock_base::Winsock_base()
{
	WSAStartup( MAKEWORD(2,0), &this->m_Wsa);
}

bool Winsock_base::CreateSocket(int af, int type, int protocol)
{
	this->m_Family = af;
	this->m_Sock = socket( af, type, protocol );

	if(this->m_Sock == SOCKET_ERROR){
		return false;
	}

	return true;
}

bool Winsock_base::Connect(char *pIpAddr, unsigned short Port)
{
	this->m_IpAddr = gethostbyname(pIpAddr);
	this->m_Port = Port;

	this->m_Sockinf.sin_family = this->m_Family;
	this->m_Sockinf.sin_port = htons(this->m_Port);
	this->m_Sockinf.sin_addr.s_addr = ((struct in_addr *)(this->m_IpAddr->h_addr))->s_addr;
	memset(this->m_Sockinf.sin_zero, 0, sizeof(this->m_Sockinf.sin_zero));

	int iError;
	iError = connect( this->m_Sock, (LPSOCKADDR) &this->m_Sockinf, sizeof(this->m_Sockinf) );
	
	if(iError == SOCKET_ERROR){
		return false;
	}

	return true;
}

int Winsock_base::Recv(char *Buffer, int Bufferlen)
{
	int size;
	size = recv(this->m_Sock, reinterpret_cast<char*>(Buffer), Bufferlen, 0);

	if(size <= 0){
		return 0;
	}

	return size;
}

bool Winsock_base::Send(const char *Buffer, int Bufferlen)
{
	int iError;
	iError = send(this->m_Sock, Buffer, Bufferlen, 0);

	if(iError == SOCKET_ERROR){
		return false;
	}

	return true;
}

Winsock_base::~Winsock_base()
{
	closesocket(this->m_Sock);
	WSACleanup();
}