#ifndef SOCKETLIST_H
#define SOCKETLIST_H

#include "TCPSocket.h"
#include <list>
#include <vector>
using namespace std;
class SocketList
{
public:
	SocketList(string ConnectIp = "127.0.0.1");
	~SocketList();
	void SendToServer(string str);              //����һ���ַ�����������
	list<string> Listening();//����������Ϣ

private:
	//list<DataSocket*> SerDatSockList;//��������������ÿ����ͻ���ͨ�ŵ������׽���
	fd_set rset;              //�׽��ּ�������������������׽���
	struct timeval zerotime;  //used in select() call
	BaseSocket *ConnectSocket;
};

#endif
