#include <mysql.h>
#include <iostream>
#include <list>
#include "CSql.h"
#include "DB.h"

using namespace std;

// ���캯��
CSql::CSql(DB* parent)
{
	db = parent;

	con = mysql_init(NULL); //��ʼ��Mysql���ݿ�
    
	if (con != NULL && mysql_real_connect(
		con, db->ip.c_str(), db->username.c_str(),
		db->passwd.c_str(), db->dbname.c_str(),
		db->port, NULL, 0))
	{
		// �趨��ǰ��������ݿ�
		if (!mysql_select_db(con, db->dbname.c_str()))
		{
			cout << db->dbname << "���ݿ����ӳɹ�!" << endl;
			con->reconnect = 1;

			// �������ı���
			if (mysql_real_query(con, "SET NAMES GBK;", strlen("SET NAME GBK;")))
			{
				cout << "�ַ�������ʧ��: " << mysql_error(con) << endl;
				system("pause");
				exit(0);
			}
		}
	}
	else
	{
		cout << db->dbname << "���ݿ�����ʧ��: " << mysql_error(con) << endl;
		system("pause");
		exit(0);
	}
}

// ��������
CSql::~CSql()
{
	mysql_close(con);
	cout << "�ͷ���1�����ӣ�" << endl;
}


// ִ��һ��sql���
bool CSql::sql(string sql_s)
{
	const char* sql = sql_s.c_str();
	int rt = mysql_real_query(con, sql, strlen(sql));
	if (rt) {
		cout << sql_s << "������Ϣ�� " << mysql_error(con) << endl;
		return false;
	}
	else
		return true;
}

// ִ��Ԥ�������
bool CSql::prepareStmt(string sql_s, MYSQL_BIND* params)
{
	const char* sql = sql_s.c_str();
	MYSQL_STMT *stmt = mysql_stmt_init(con); //����MYSQL_STMT���
	if (mysql_stmt_prepare(stmt, sql, strlen(sql)))
	{
		cout << sql_s << "Ԥ��������ʼ��ʧ��: " << mysql_error(con);
		return false;
	}
	mysql_stmt_bind_param(stmt, params);
	mysql_stmt_bind_result(stmt, params);
	mysql_stmt_execute(stmt);      //ִ��Ԥ����
	mysql_stmt_store_result(stmt); //�Ա������mysql_stmt_fetch()�����ܷ��ػ�������
	string err = mysql_stmt_error(stmt);
	mysql_stmt_close(stmt);
	if (err == ""){
		return true;
	}
	else{
		cout << "������Ϣ: " << err << endl;
		return false;
	}
}

// �����Զ��ύ����
bool CSql::openAutoCommit()
{
	return this->sql("set autocommit=1;");
}

// �����ֶ��ύ����
bool CSql::openManuCommit()
{
	return this->sql("set autocommit=0;");
}

// ����ع�
bool CSql::rollBack()
{
	return this->sql("rollback;");
}

// �����ύ
bool CSql::commit()
{
	return this->sql("commit;");
}

// �����ѯ����������ز�ѯ������������
unsigned int CSql::putOutRes(bool b)
{
	unsigned int t, j, count = 0;
	MYSQL_RES *res = mysql_store_result(con);
	MYSQL_ROW row;
	MYSQL_FIELD *fd;    //�ֶ�������
	list<string> field; //�ֶ�������
	
	if (b)
	{
		// ��ȡ�ֶ���
		for (int i = 0; fd = mysql_fetch_field(res); i++)
			field.push_back(fd->name);
		// ��ȡ����
		j = mysql_num_fields(res);
		// ��ӡ�ֶ�
		for (int i = 0; i < j; i++) {
			cout << field.front() << "\t";
			field.pop_front();
		}
		cout << endl;
	}

		// �ӵ�ǰ������л�ȡ���ݣ���������һ�У�ȡ�����һ�з���false
	while (row = mysql_fetch_row(res))
	{
		if (b)
		{
			for (t = 0; t < j; t++)
				if (row[t] == NULL)
					cout << "NULL\t";
				else
					cout << row[t] << "\t";
		    cout << endl;
	    }
		count++;
	}
	if(b)
	    cout << "��ѯ���������" << count << endl;

	// �ͷŽ����
	mysql_free_result(res);

	return count;
}