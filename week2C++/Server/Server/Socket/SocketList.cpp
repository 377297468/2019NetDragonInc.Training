#include <iostream>
#include "SocketList.h"
#include "json.hpp"
#include "../Chat.h"

using json = nlohmann::json;

SocketList::SocketList(bool IsServer, string ConnectIp)
{
	zerotime.tv_usec = 0;
	zerotime.tv_sec = 0;
	ConnectSocket = new ListenSocket;
}

SocketList::~SocketList()
{
	delete ConnectSocket;
	for (list<DataSocket*>::iterator itr = SerDatSockList.begin();
		itr != SerDatSockList.end(); itr++)
	{
		delete *itr;
	}
}

list<string> SocketList::Listening(Chat* chat,DataSocket **RecSocket)
{
	list<string> retDataList;

	// ��ʼ��rsetΪNULL
	FD_ZERO(&rset);

	// ������������׽���
	FD_SET(ConnectSocket->GetSocket(), &rset);

	// ������������׽�������
	for (list<DataSocket*>::iterator itr = SerDatSockList.begin(); itr != SerDatSockList.end(); itr++)
	{
		FD_SET((*itr)->GetSocket(), &rset);
	}

	// ������rset���Ƿ��л���׽���
	int i = select(0x7FFFFFFF, &rset, NULL, NULL, &zerotime);
	if (i > 0)
	{
		ListenSocket* listenSocket = dynamic_cast<ListenSocket*> (ConnectSocket);
		if (FD_ISSET(listenSocket->GetSocket(), &rset)) //�յ��µ���������
		{
			DataSocket *dsock = listenSocket->AcceptConnect();
			SerDatSockList.push_back(dsock); //���յ������׽������
			*RecSocket = dsock;
			json j = {
				{"instruct",true},
				{"str","Connected"}
			};
			retDataList.push_back(j.dump() + "#end#");//��Ϣ���
		}
		// ����ÿ��socket����Ƿ��л
		for (list<DataSocket*>::iterator itr = SerDatSockList.begin(); itr != SerDatSockList.end(); itr++)
		{
			if (FD_ISSET((*itr)->GetSocket(), &rset))
			{
				string mes = (*itr)->ReceiveData();
				if (mes == "SocketClosed")  //�ͻ��˹ر�
				{
					std::cout << "��һ���ͻ��˹ر���" << std::endl;
					chat->nameInRoom.clear();
					json j = {
				        {"instruct",true},
				        {"str","ReConnect"}
					};
					retDataList.push_back(j.dump() + "#end#");//��Ϣ���

					delete (*itr);
					itr = SerDatSockList.erase(itr);
					if (itr == SerDatSockList.end())
						break;
					continue;
				}
				else
				{
					retDataList.push_back(mes + "#end#");//��Ϣ���
					*RecSocket = *itr;
				}
			}
		}
		// �㲥��Ϣ��
		if (retDataList.size() != 0)
			SendToAllClient(retDataList);
	}
	return retDataList; //������Ϣ��
}

void SocketList::SendToAllClient(list<string> StrList)
{
	for (list<string>::iterator sItr = StrList.begin(); sItr != StrList.end(); sItr++)
	{
		SendToAllClient(*sItr);
	}
}

void SocketList::SendToAllClient(string str)
{
	for (list<DataSocket*>::iterator itr = SerDatSockList.begin(); itr != SerDatSockList.end(); itr++)
	{
		(*itr)->SendData(str);
	}
}