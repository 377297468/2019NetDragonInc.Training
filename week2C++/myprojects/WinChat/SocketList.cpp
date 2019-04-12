#include "Socket/SocketList.h"

SocketList::SocketList(bool IsServer, string ConnectIp) :isServer(IsServer)
{
	zerotime.tv_usec = 0;
	zerotime.tv_sec = 0;
	if (isServer)
		ConnectSocket = new ListenSocket;
	else
	{
		ConnectSocket = new DataSocket;
		DataSocket* dataSocket = dynamic_cast<DataSocket*> (ConnectSocket);
		dataSocket->RequestConnect(ConnectIp);
	}
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

void SocketList::Send(string str)
{
	if (isServer)
		SendToAllClient(str);
	else
		SendToServer(str);
}

list<string> SocketList::Listening(DataSocket **RecSocket)
{
	chat::data proto_data;
	list<string> retDataList;
	FD_ZERO(&rset);// ��ʼ��rsetΪNULL
	FD_SET(ConnectSocket->GetSocket(), &rset);// ������������׽���
	if (isServer)
	{
		// ������������׽�������
		for (list<DataSocket*>::iterator itr = SerDatSockList.begin();itr != SerDatSockList.end(); itr++)
		{
			FD_SET((*itr)->GetSocket(), &rset);
		}
	}
	// ������rset���Ƿ��л���׽���
	int i = select(0x7FFFFFFF, &rset, NULL, NULL, &zerotime);
	if (i > 0)
	{
		if (!isServer)  //�ͻ���
		{
			DataSocket* dataSocket = dynamic_cast<DataSocket*> (ConnectSocket);
			if (FD_ISSET(dataSocket->GetSocket(), &rset)) //���յ���������������Ϣmes
			{
				string mes = dataSocket->ReceiveData();
				if (mes == "SocketClosed")
				{
					MessageBox(NULL, L"The server is closed!", L"Prompt", 0);
					exit(0);
				}
				proto_data.set_ins(mes);
				string* output = NULL;
				output = new string;
				proto_data.SerializeToString(output);
				retDataList.push_back(*output + "#end#");//��Ϣ����ȴ�Chat��Ĵ���
				delete output;
			}
		}
		else if (isServer) //�����
		{
			ListenSocket* listenSocket = dynamic_cast<ListenSocket*> (ConnectSocket);
			if (FD_ISSET(listenSocket->GetSocket(), &rset)) //����Socket�ܵ���������
			{
				DataSocket *dsock = listenSocket->AcceptConnect();// ��������
				SerDatSockList.push_back(dsock);// ���յ������׽������
				*RecSocket = dsock;
				proto_data.set_ins("Connected");
				string* output = NULL;
				output = new string;
				proto_data.SerializeToString(output);
				retDataList.push_back(*output + "#end#");//��Ϣ����ȴ�Chat��Ĵ���
				delete output;
			}
			// ����ÿ��socket����Ƿ��л
			for (list<DataSocket*>::iterator itr = SerDatSockList.begin();itr != SerDatSockList.end(); itr++)
			{
				if (FD_ISSET((*itr)->GetSocket(), &rset))
				{
					string mes = (*itr)->ReceiveData();
					if (mes == "SocketClosed")  //�ͻ��˹ر���Ϣ
					{
						delete (*itr);
						itr = SerDatSockList.erase(itr);
						if (itr == SerDatSockList.end())
							break;
						continue;
					}
					else  //������Ϣ
					{
						proto_data.set_ins(mes);
						string* output = NULL;
						output = new string;
						proto_data.SerializeToString(output);
						retDataList.push_back(*output + "#end#");//��Ϣ����ȴ�Chat��Ĵ���
						delete output;
						*RecSocket = *itr;
					}
				}
			}
			//endfor
			if (retDataList.size() != 0)
			{
				SendToAllClient(retDataList);
			}
		}
	}
	return retDataList;
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
	for (list<DataSocket*>::iterator itr = SerDatSockList.begin();itr != SerDatSockList.end(); itr++)
	{
		(*itr)->SendData(str);
	}
}

void SocketList::SendToServer(string str)
{
	DataSocket *dataSocket = dynamic_cast<DataSocket *>(ConnectSocket);
	dataSocket->SendData(str);
}