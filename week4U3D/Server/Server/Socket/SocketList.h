#ifndef SOCKETLIST_H
#define SOCKETLIST_H

#include "TCPSocket.h"
#include <list>

class Room;

using namespace std;
class SocketList
{
public:
	SocketList();
	~SocketList();

	// ����������Ϣ
	list<string> Listening(Room* chat,DataSocket **RecSocket = NULL);
	
	// �㲥һ���ַ���
	void SendToAllClient(string str);

private:
	list<DataSocket*> SerDatSockList;//����������ͻ���ͨ�ŵ������׽���
	fd_set rset;                     //�׽��ּ���������������׽���
	struct timeval zerotime;         //used in select() call
	BaseSocket *ConnectSocket;
	void SendToAllClient(list<string> StrList); //�㲥�ַ�������
};

#endif
