#pragma once
#include "Socket/TCPSocket.h"
#include "Socket/SocketList.h"
#include "Thread/ThreadLib.h"

using namespace std;

class Chat
{
public:
	Chat();
	~Chat();

	string myName;      //�Լ�������
	bool alreadyCon = false;
	void Fresh();       //ˢ��
	void EnterRoom();   //���뷿�䣬�����ͻ���
	static void CinString(void *Receive); //����������Ϣ

	vector<string> SeparateMsg(string str);//���
	bool detectingInstruct(string str);    //ָ������ִ��
	void putOutWords();   //�����Ϣ
	void detectingMsg();  //����Ƿ��յ�����Ϣ
	static SocketList* Room; //����Socketͨ�Žӿ�
	list<string> RecStrList; //������յ���Ϣ

	string getTime();  //��ȡϵͳʱ��
};