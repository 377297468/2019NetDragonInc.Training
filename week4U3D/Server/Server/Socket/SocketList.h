#ifndef SOCKETLIST_H
#define SOCKETLIST_H

#include "TCPSocket.h"
#include <list>

class Chat;

using namespace std;
class SocketList
{
public:
	SocketList(bool IsServer, string ConnectIp = "127.0.0.1");
	~SocketList();
	list<string> Listening(Chat* chat,DataSocket **RecSocket = NULL);  //����������Ϣ
	void SendToAllClient(string str);          //�㲥һ���ַ���

private:
	list<DataSocket*> SerDatSockList;//����������ͻ���ͨ�ŵ������׽���
	fd_set rset;                     //�׽��ּ���������������׽���
	struct timeval zerotime;         //used in select() call
	BaseSocket *ConnectSocket;
	void SendToAllClient(list<string> StrList); //�㲥�ַ�������
};

#endif
