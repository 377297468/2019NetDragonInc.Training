#include <algorithm>
#include <iostream>
#include "Socket/SocketList.h"
#include "Socket/json.hpp"
#include "Room.h"
#include "MySQL/DB.h"

using namespace std;
using json = nlohmann::json;

SocketList* Room::sockets = NULL;

Room::Room(): RecSocket(NULL)
{
	StartSocketLib;
	db = DB::getInstance();
	//srand(GetTickCount());
}

Room::~Room() { CloseSocketLib; }

void Room::CreateRoom()
{
	sockets = new SocketList();
	Fresh();
}

void Room::Fresh()
{
	cout << allName() << endl;
	while (true)
	{
		detectingMsg();
	}
}

// ������Ϣ
void Room::detectingMsg()
{
	RecStrList = sockets->Listening(this,&RecSocket);
	if (RecStrList.size() != 0)
		putOutWords();
}

// �ָ����ݰ�
vector<string> Room::SeparateMsg(string str)
{
	vector<string> retStrVec;
	int pos;
	while ((pos = str.find("#end#")) != string::npos)
	{
		retStrVec.push_back(str.substr(0, pos));
		str.erase(0, pos + 5);
	}
	if (str != "")
		retStrVec.push_back(str);
	return retStrVec;
}

// ִ��ָ��
bool Room::detectingInstruct(string rec_str)
{
	if (rec_str == "")
		return false;
	try{
		json j = json::parse(rec_str);
		// ����ͬ��ָ��μ���ͨѶЭ���ĵ�����
		if (j["instruct"]) {
			string str = j["str"];
			// connectָ��
			if (str == "connect")
			{
				string name = j["name"],
					pswd = j["pswd"];
				checkAccount(name, pswd);
			}
			return true;
		}
	}
	catch (exception e) 
	{
		cout << "��Ϣ����ʧ�� " << endl;
	}
	return false;
}

void Room::checkAccount(string name, string pswd)
{
	// ����name�Ƿ��Ѿ��Ѿ���¼
	list<string>::iterator iter = find(nameInRoom.begin(), nameInRoom.end(), name);
	if (iter != nameInRoom.end())
	{
		sendInfo("User \"" + name + "\" is already in the room!", false);
		return;
	}
	// �����ݿ�����û���������
	int v = db->checkAccount(name, pswd);
	if (v == 0) {
		sendInfo("Login successfully!", false);
		string oldName = RecSocket->userName;
		if (oldName != "")
			nameInRoom.remove(oldName);
		nameInRoom.push_back(name);
		RecSocket->userName = name;
		refreshNames();
	}
	else if (v == 1) {
		sendInfo("User name \"" + name + "\" does not exist!", false);
	}
	else if (v == 2) {
		sendInfo("Error password!", false);
	}
	else {
		sendInfo("Logon failed!", false);
	}
}

// ��������������˵�����
string Room::allName()
{
	string s = "The people in this room: ";
	if (nameInRoom.size() == 0)
		s += "No People";
	else
		for (list<string>::iterator itr = nameInRoom.begin(); itr != nameInRoom.end(); itr++)
			s = s + *itr + " ";
	return s;
}

// ˢ�·����������˵����֣����㲥���ͻ��ˣ�
void Room::refreshNames()
{
	sendInfo(allName());
	cout << allName() << endl;
}

// ��ͻ��˷���һ���ı�
// toAll true:�㲥 fasle:���͸���ǰRecSocket
void Room::sendInfo(string s, bool toAll) {
	json j = {
		{"instruct",false},
		{"name","Server"},
		{"time",""},
		{"str",s}
	};
	if (toAll)
		sockets->SendToAllClient(j.dump() + "#end#");
	else
		RecSocket->SendData(j.dump() + "#end#");
}

// ��ʾ��������Ϣ
void Room::putOutWords()
{
	for (list<string>::iterator itr = RecStrList.begin(); itr != RecStrList.end(); itr++)
	{
		vector<string> msgVector = SeparateMsg(*itr);
		for (vector<string>::iterator it = msgVector.begin(); it != msgVector.end(); it++)
		{
			cout << *it << endl;
			detectingInstruct(*it);
		}
	}
}