#pragma once

using namespace std;

class CSql;
class ConnPool;

class DB
{
public:
	~DB();

	// ��ȡ��������
	static DB* getInstance();

	// ����user�˻�
	bool createAccount(string name, string passwd);

    // У���û���������
	// 0:У��ɹ� 1:�û��������� 2:������� 3:����ԭ����У��ʧ��
	int checkAccount(string name, string passwd);

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
	string dbname = "game";
	int port = 3306;

	// ���ӳ�
	ConnPool* pool;
	int poolSize = 5; //��СΪ5
	
	// ��ȡϵͳʱ��
	string getTime();
};