#pragma once

#include <list>
#include <mutex>

using namespace std;

class DB;
class CSql;

class ConnPool
{
public:
	// ��ȡ���ݿ����ӳض���
	static ConnPool* getInstance(DB* db, int size);
	// �õ�һ������
	CSql* getConnect();
	// �黹һ������
	void retConnect(CSql* ret);
	// ��ȡ���ӳص�ʣ��������
	size_t getPoolSize();

	~ConnPool();

private:
	static ConnPool *pool; //���ӳض���
	mutex lock;            //��
	int poolSize;          //���ӳش�С
	list<CSql*> conList;   //���Ӷ���

	// ����ģʽ ���캯��
	ConnPool(DB* db, int maxSize);
};
