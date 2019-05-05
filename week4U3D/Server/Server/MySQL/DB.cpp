#include <time.h>
#include "DB.h"
#include "CSql.h"
#include "ConnPool.h"

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

////////////////////////////////
/// �����˻�
////////////////////////////////
bool DB::createAccount(string name_s)
{
	// ���̳߳���ȡ������
	CSql* c = pool->getConnect();

	// �޸����ݿ��ύģʽΪ�ֶ��ύ
	if (c->openManuCommit())
	{
		// ��ʼ������
		if (c->sql("start transaction;"))
		{
			char* name = (char*)name_s.c_str();
			MYSQL_BIND param[1];
			memset(param, 0, sizeof(param));
			param[0].buffer_type = MYSQL_TYPE_STRING;
			param[0].buffer = name;
			param[0].buffer_length = strlen(name);

			// ����user��¼
			string sql = "insert into user(user_name) values(?);";
			if (c->prepareStmt(sql, param))
			{
				// ����role��¼
				string sql = "insert into role(user_name) values(?);";
				if(c->prepareStmt(sql, param))
				{ 
					// �����ύ
					if (c->commit())
					{
						c->openAutoCommit();
						pool->retConnect(c);
						return true;
					}
				}
				else
				{
					// ����ع�
					c->rollBack();
				}
			}
			else
			{
				// ����ع�
				c->rollBack();
			}
		}
	}
	c->openAutoCommit();
	pool->retConnect(c);
	return false;
}

//////////////////////////////
/// �޸��û���
//////////////////////////////
bool DB::changeUserName(string newname, string oldname)
{
	// ���̳߳���ȡ������
	CSql* c = pool->getConnect();

	// �޸����ݿ��ύģʽΪ�ֶ��ύ
	if (c->openManuCommit())
	{
		// ��ʼ������
		if (c->sql("start transaction;"))
		{
			char *nameNew = (char*)newname.c_str(),
				*nameOld = (char*)oldname.c_str();
			MYSQL_BIND params[2];
			memset(params, 0, sizeof(params));
			params[0].buffer_type = MYSQL_TYPE_STRING;
			params[0].buffer = nameNew;
			params[0].buffer_length = strlen(nameNew);
			params[1].buffer_type = MYSQL_TYPE_STRING;
			params[1].buffer = nameOld;
			params[1].buffer_length = strlen(nameOld);
			string sql = "update user set user_name=? where(user_name=?);";
			if (c->prepareStmt(sql, params))
			{
				// �����ύ
				if (c->commit())
				{
					c->openAutoCommit();
					pool->retConnect(c);
					return true;
				}
			}
			else
			{
				// ����ع�
				c->rollBack();
			}
		}
	}
	c->openAutoCommit();
	pool->retConnect(c);
	return false;
}

////////////////////////////
/// ɾ���û�����
////////////////////////////
bool DB::deleteUser(string name)
{
	CSql* c = pool->getConnect();
	if (c->openManuCommit())
	{
		if (c->sql("start transaction;"))
		{
			string sql = "select * from user where(user_name='" + name + "');";
			if (c->sql(sql)){
				// ��ѯname�Ƿ����
				if(c->putOutRes(false)>0){
					sql = "delete from user where(user_name='" + name + "');";
					if (c->sql(sql))
						if (c->commit())
						{
							c->openAutoCommit();
							pool->retConnect(c);
							return true;
						}
						else
							c->rollBack();
				}
				else {
					c->rollBack();
					cout << "�û�" << name << "�����ڣ�" << endl;
				}
			}
			else
				c->rollBack();
		}
	}
	c->openAutoCommit();
	pool->retConnect(c);
	return false;
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
