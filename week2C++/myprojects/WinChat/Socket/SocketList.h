#ifndef SOCKETLIST_H
#define SOCKETLIST_H

#include "TCPSocket.h"
#include "data.pb.h"
#include <list>
#include <vector>
using namespace std;
class SocketList
{
public:
	SocketList(bool IsServer, string ConnectIp = "127.0.0.1");//����������/�ͻ���
	~SocketList();
	void Send(string str);//������Ϣ
	list<string> Listening(DataSocket **RecSocket = NULL);//����������Ϣ
private:
	void SendToAllClient(list<string> StrList);//���ַ��������͵����пͻ���
	void SendToAllClient(string str);//��һ���ַ������͵����пͻ���
	void SendToServer(string str);//��һ���ַ������͵�������
	list<DataSocket*> SerDatSockList;//��������������ÿ����ͻ���ͨ�ŵ������׽���
	fd_set rset;//�׽��ּ�������������������׽���
	struct timeval zerotime;//���ṹ���ʾ��������
	BaseSocket *ConnectSocket;//����/���ӵ�ʱ���õ��׽���
	bool isServer;//�Ƿ�Ϊ������
};

#endif
