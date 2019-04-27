#pragma once

class DB;

class CSql
{
private:
	DB* db;     //���ݿ�
	MYSQL* con; //���Ӷ���

public:
	CSql(DB* db);
	~CSql();

	// ִ��һ��sql���
	bool sql(std::string sql_s);

	// ִ��Ԥ�������
	bool prepareStmt(std::string sql_s, MYSQL_BIND* params);

	// �����Զ��ύ����
	bool openAutoCommit();

	// �����ֶ��ύ����
	bool openManuCommit();

	// ����ع�
	bool rollBack();

	// �����ύ
	bool commit();

	/**
	 * @brief �����ѯ�Ľ��
	 *
	 * @param b �Ƿ��������Ļ
	 * @return ��ѯ������������
	 */
	unsigned int putOutRes(bool b = true);
};