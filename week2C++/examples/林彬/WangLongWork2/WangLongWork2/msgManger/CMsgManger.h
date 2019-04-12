#pragma once
#include <list>
#include <Mutex>
#include <iostream>
#include "../msgManger/commun.pb.h"
#define MSGCOUNT 10000
#define BUFFSIZE 1024
#include <windows.h>

class CMsgManger
{
public:
	~CMsgManger();
	static CMsgManger * getSingleton();
	//��������ݶ����в�����ܵ�������
	void insertReceiveMsg(void * pdata);
	//�ӽ������ݶ����л�ȡ���ܵ�������
	void *getReceiveMsg();
	//�������ݶ����в���Ҫ���͵�����
	void insertSendMsg(void * pdata);
	//�ӷ������ݶ����л�ȡҪ���͵�����
	void *getSendMsg();
	void msgRecvDequeDeal();
	void msgSendDequeDeal();
	void setFdArray(fd_set fdRead);

private:
	CMsgManger();
	static CMsgManger *msgmanger;
	std::list<void *> m_msgRecvList;
	std::list<void *> m_msgSendList;
	std::list<void *>::iterator it;
	HANDLE m_semSendInsertList;
	HANDLE m_semSendGetList;
	HANDLE m_semRecvInsertList;
	HANDLE m_semRecvGetList;
	std::thread  recvThread;
	std::thread  sendThread;
	std::mutex m_recvMutex;
	std::mutex m_sendMutex;
	bool isRun;
	fd_set m_fdRead;

	class CGarBo
	{
	public:
		CGarBo() {}
		~CGarBo()
		{
			if (msgmanger != NULL)
				delete msgmanger;
		}
	};
	static CGarBo GarBo;
};
