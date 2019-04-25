#include "pch.h"
#include "ConnPool.h"
#include "mysql_connect.h"

using namespace std;

ConnPool* ConnPool::pool = nullptr;

// ���캯��(private)
ConnPool::ConnPool(string name, string pwd, string nurl, int maxSize) :	username(name), password(pwd), url(nurl), poolSize(maxSize)
{
	driver = get_driver_instance(); //��ȡmysql����
	lock_guard<mutex> locker(lock); //��������������ʱ�Զ�������
	addConn(poolSize);              //��������
}

// �������ӳ�
ConnPool::~ConnPool()
{
	for (auto &conn : conList)
	{
		// ����ת������Ȩ����������ʱ���ر����ӣ���������ʱ����ָ���Զ��ͷ�
		shared_ptr<Connection> &&sp = move(conList.front());
		sp->close();
	}
}

int ConnPool::getPoolSize()
{
	return conList.size();
}

void ConnPool::addConn(int size)
{
	for (int i = 0; i < size; ++i)
	{
		// ��������
		Connection *conn = driver->connect(url, username, password);
		shared_ptr<Connection> sp(conn, [](Connection *conn) {	delete conn; });
		conList.push_back(move(sp));
	}
}

ConnPool* ConnPool::getInstance()
{
	if (pool == nullptr)
		pool = new ConnPool("root", "", "127.0.0.1:3306", 10); //����10������
	return pool;
}

shared_ptr<Connection> ConnPool::getConnect()
{
	lock_guard<mutex> locker(lock);
	shared_ptr<Connection> sp = conList.front();
	conList.pop_front();
	return sp;
}

void ConnPool::retConnect(shared_ptr<Connection> &ret)
{
	lock_guard<mutex>locker(lock);
	conList.push_back(ret);
}
