#include "pch.h"
#include "CSql.h"


CSql::CSql()
{
	// ��ʼ��MySql���ݿ�
	pConn = mysql_init(NULL);

	// �������ݿ�
	MYSQL* p = (MYSQL*)pConn;
	if (mysql_real_connect(p, "localhost", "root", "", "chat", 0, NULL, 0))
	    std::cout << "�������ݿ�ɹ�!" << std::endl;
	else{
		std::cout << "�޷��������ݿ�! ������Ϣ: " << mysql_error(p) << std::endl;
		//MessageBox(NULL, L"�޷��������ݿ�!", L"Prompt", 0);
		system("pause");
		exit(0);
	}
}


CSql::~CSql()
{
	delete pConn;
}
