#pragma once

//c++
#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <functional>

//mysql driver
#include <mysql_driver.h>
#include <mysql_connection.h>

//mysql execute
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <exception>

//thread mutex 
#include <mutex>

using namespace sql;
using namespace std;

class ConnPool
{
public:
	// ��ȡ���ݿ����ӳض���
	static ConnPool* getInstance();
	// �õ�һ������
	shared_ptr<Connection> getConnect();
	// �黹һ������
	void retConnect(shared_ptr<Connection> &ret);

	~ConnPool();
	int getPoolSize();

private:
	static ConnPool *pool; //���ӳض���
	mutex lock;       //��
	Driver *driver;        //mysql driver
	int poolSize;          //���ӳش�С
	string username;
	string password;
	string url;
	list<shared_ptr<Connection>> conList; //���Ӷ���

	ConnPool(string name, string pwd, string nurl, int maxSize);
	void addConn(int size);
};
