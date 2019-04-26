#include "pch.h"
#include "CSql.h"
#include "ConnPool.h"

using namespace std;

ConnPool* ConnPool::pool = nullptr;

// ���캯��(private)
ConnPool::ConnPool(DB* db, int maxSize)
	: poolSize(maxSize)
{
	// ��������������ʱ�Զ�������
	lock_guard<mutex> locker(lock);

	// ����poolSize������
	for (int i = 0; i < poolSize; ++i)
	{
		CSql* p = new CSql(db);
		conList.push_back(p);
	}
}

// �������ӳ�
ConnPool::~ConnPool()
{
	for (auto p : conList)
	{
		delete p;
	}
	pool = nullptr;
	cout << "���ӳ������٣�" << endl;
}

size_t ConnPool::getPoolSize()
{
	return conList.size();
}

ConnPool* ConnPool::getInstance(DB* db, int size)
{
	if (pool == nullptr)
		pool = new ConnPool(db, size);
	return pool;
}

CSql* ConnPool::getConnect()
{
	lock_guard<mutex> locker(lock);
	CSql* p = conList.front();
	conList.pop_front();
	return p;
}

void ConnPool::retConnect(CSql* ret)
{
	lock_guard<mutex>locker(lock);
	conList.push_back(ret);
}
