#include "pch.h"
#include "DB.h"


DB::DB()
{
}


DB::~DB()
{
}


MYSQL * DB::connect()
{
	con = mysql_init(NULL); //��ʼ��Mysql���ݿ�
	// 
	if (con != NULL && mysql_real_connect(con, ip, user, passwd, dbname, 3306, NULL, 0))
	{
		// �趨��ǰ��������ݿ�
		if (!mysql_select_db(con, dbname))
		{
			cout << "mysql_select_db�ɹ�!" << endl;
			con->reconnect = 1;

			// �������ı���
			if (mysql_real_query(con, "SET NAMES GBK;", (unsigned int)strlen("SET NAME GBK;")))
			{
				cout << "�ַ�������ʧ��: " << mysql_error(con) << endl;
				system("pause");
				exit(0);
			}
		}
	}
	else
	{
		cout << dbname << "���ݿ�����ʧ��: " << mysql_error(con) << endl;
		system("pause");
		exit(0);
	}
	return con;
}