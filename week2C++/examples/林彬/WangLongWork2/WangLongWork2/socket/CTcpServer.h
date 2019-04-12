#pragma once
#include "CSocketBase.h"
#include "../msgManger/CMsgManger.h"
class CTcpServer: public CSocketBase
{
public:
	CTcpServer();
	CTcpServer(char *ip, unsigned short port);
	void Bind();
	void Listen();
	SOCKET Accept();
	//��ʼlisten�ͻ���
	void clientListen();
	//�����ͻ��ˣ�������select������Ӧ����
	void Recv();
protected:
	CMsgManger *m_msgManger;
};