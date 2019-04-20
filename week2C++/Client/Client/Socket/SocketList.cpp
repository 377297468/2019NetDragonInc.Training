#include "SocketList.h"

SocketList::SocketList(string ConnectIp)
{
	zerotime.tv_usec = 0;
	zerotime.tv_sec = 0;

	ConnectSocket = new DataSocket;
	DataSocket* dataSocket = dynamic_cast<DataSocket*> (ConnectSocket);
	dataSocket->RequestConnect(ConnectIp);
}

SocketList::~SocketList()
{
	delete ConnectSocket;
	//for (list<DataSocket*>::iterator itr = SerDatSockList.begin();
	//	itr != SerDatSockList.end(); itr++)
	//{
	//	delete *itr;
	//}
}

list<string> SocketList::Listening()
{
	list<string> retDataList;

	// ��ʼ��rsetΪNULL
	FD_ZERO(&rset);

	// ������������׽���
	FD_SET(ConnectSocket->GetSocket(), &rset);

	// ������rset���Ƿ��л���׽���
	int i = select(0x7FFFFFFF, &rset, NULL, NULL, &zerotime);
	if (i > 0)
	{
		DataSocket* dataSocket = dynamic_cast<DataSocket*> (ConnectSocket);
		if (FD_ISSET(dataSocket->GetSocket(), &rset))
		{
			string mes = dataSocket->ReceiveData();
			if (mes == "SocketClosed")
			{
				MessageBox(NULL, L"The server is closed!", L"Prompt", 0);
				exit(0);
			}
			retDataList.push_back(mes + "#end#");//��Ϣ����ȴ�����
		}

	}
	return retDataList; //������Ϣ��
}

void SocketList::SendToServer(string str)
{
	DataSocket *dataSocket = dynamic_cast<DataSocket *>(ConnectSocket);
	dataSocket->SendData(str);
}