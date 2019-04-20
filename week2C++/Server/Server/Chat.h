#pragma once
#include <vector>
#include <list>
#include <string>

using namespace std;

class SocketList;
class DataSocket;

class Chat
{
public:
	Chat();
	~Chat();

	void Fresh();       //ˢ��
	void CreateRoom();  //�������䣬����������
	string allName();   //�����������˵�����
	list<string> nameInRoom;

	vector<string> SeparateMsg(string str);//���
	bool detectingInstruct(string str);    //ָ������ִ��
	void putOutWords();   //��ʾ������Ϣ
	void detectingMsg();  //�����µ���Ϣ

	static SocketList* sockets; //����Socketͨ�Žӿ�
	DataSocket* RecSocket;   //���淢����Ϣ��Socket
	list<string> RecStrList; //������յ���Ϣ
};