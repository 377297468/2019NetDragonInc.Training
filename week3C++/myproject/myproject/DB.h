#pragma once

using namespace std;

class CSql;
class ConnPool;

// ��ɫ���ͣ��û����οͣ�����Ա
enum RoleType { user, wander, admin };

class DB
{
public:
	~DB();

	// ��ȡ��������
	static DB* getInstance();

	// ����user�˻�
	bool createAccount(string name);
	// �޸��û���
	bool changeUserName(string newname, string oldname);
	// ɾ��ĳ�û�
	bool deleteUser(string name);
	// ������б�
	void printAllTable();

private:
	// SQL������
	friend CSql;

	// ���ݿ�
	DB();
	static DB* db;
	string username = "root";
	string passwd = "";
	string ip = "localhost";
	string dbname = "chat";
	int port = 3306;

	// ���ӳ�
	ConnPool* pool;
	int poolSize = 5; //��СΪ5
	
	// ��ȡϵͳʱ��
	string getTime();
};