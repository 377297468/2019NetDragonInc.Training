#include <time.h>
#include <iostream>
#include "DB.h"
#include "CSql.h"
#include "ConnPool.h"

using namespace std;

DB* DB::db = nullptr;

DB::DB()
{
	pool = ConnPool::getInstance(this, poolSize);
}

DB::~DB()
{
	delete pool;
	pool = nullptr;
	db = nullptr;
	cout << "db�����٣�" << endl;
}

DB* DB::getInstance()
{
	if (db == nullptr)
		db = new DB();
	return db;
}

// ������б�
void DB::printAllTable()
{
	// ��ȡ����
	CSql* con = pool->getConnect();

	cout << getTime() << " ������ݿ�chat���ݣ�" << endl;
	cout << "----------- user ------------" << endl;
	string tmp = "select * from user";
	con->sql(tmp);
	con->putOutRes();
	cout << "----------- role ------------" << endl;
	tmp = "select * from role";
	con->sql(tmp);
	con->putOutRes();
	cout << "---------- record -----------" << endl;
	tmp = "select * from record";
	con->sql(tmp);
	con->putOutRes();

	// �黹����
	pool->retConnect(con);
}

// �����˻�
bool DB::createAccount(string name_s, string passwd)
{
	// ���̳߳���ȡ������
	CSql* c = pool->getConnect();

	char* name = (char*)name_s.c_str();
	char* pswd = (char*)passwd.c_str();
	MYSQL_BIND param[2];
	memset(param, 0, sizeof(param));
	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer = name;
	param[0].buffer_length = strlen(name);
	param[1].buffer_type = MYSQL_TYPE_STRING;
	param[1].buffer = pswd;
	param[1].buffer_length = strlen(pswd);
	string sql = "insert into user(user_name,pass_word) values(?,?);";
	if (c->prepareStmt(sql, param))
	{
		pool->retConnect(c);
		return true;
	}
	else
	{
		pool->retConnect(c);
		return false;
	}
}

/**
 * @brief У���û���������
 *
 * @param name �û���
 * @param passwd ����
 * @return int 0:У��ɹ� 1:�û��������� 2:������� 3:����ԭ����У��ʧ��
**/
int DB::checkAccount(string name, string passwd)
{
	CSql* c = pool->getConnect();
	if (c->openManuCommit())
	{
		if (c->sql("start transaction;"))
		{
			string sql = "select * from user where(user_name='" + name + "');";
			if (c->sql(sql)) {
				// ��ѯname�Ƿ����
				if (c->putOutRes(false) == 1) {
					sql = "select * from user where(user_name='" + name + "' and pass_word='" + passwd + "');";
					if (c->sql(sql))
						// ��ѯpasswd�Ƿ����
						if (c->putOutRes(false) == 1)
						{
							c->openAutoCommit();
							pool->retConnect(c);
							return 0;
						}
						else {
							c->rollBack();
							cout << "�������" << endl;
							c->openAutoCommit();
							pool->retConnect(c);
							return 2;
						}
				}
				else {
					c->rollBack();
					cout << "�û�" << name << "�����ڣ�" << endl;
					c->openAutoCommit();
					pool->retConnect(c);
					return 1;
				}
			}
		}
	}
	c->rollBack();
	c->openAutoCommit();
	pool->retConnect(c);
	return 3;
}

// ��ȡϵͳʱ��
string DB::getTime()
{
	char tmp[32];
	struct tm timeInfo;
	time_t t = time(0);
	localtime_s(&timeInfo, &t);
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %X", &timeInfo);

	return string(tmp);
}
