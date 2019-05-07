#pragma once
#include <vector>
#include <list>
#include <string>

using namespace std;

class SocketList;
class DataSocket;
class DB;

class Room
{
public:
	Room();
	~Room();
	void CreateRoom();       //�������䣬����������
	void refreshNames();     //�ÿͻ���ˢ�·����������˵�����
	void sendInfo(string s, bool toAll = true); //��ͻ��˷�����Ϣ

	list<string> nameInRoom; //���������û����ֶ���

private:
	void Fresh();        //ˢ��
	string allName();    //�����������˵�����
	void putOutWords();  //��ʾ��Ϣ
	void detectingMsg(); //������Ϣ
	vector<string> SeparateMsg(string str);//���
	bool detectingInstruct(string str);    //ָ������ִ��
	// У���û���������
	void checkAccount(string name, string pswd);

	static SocketList* sockets; //�������Socketͨ�Žӿ�
	DataSocket* RecSocket;      //���淢����Ϣ��Socket
	list<string> RecStrList;    //���յ�����Ϣ����
	DB* db;
};