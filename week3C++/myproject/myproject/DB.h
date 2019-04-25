#pragma once

#include <string>
using namespace std;

// ��ɫ���ͣ��οͣ��û�������Ա
enum role_type { wander, user, admin };

class DB
{
public:
	char user[20] = "root";
	char passwd[20] = "";
	char ip[20] = "localhost";
	char dbname[10] = "chat";

	// ���ӳ�
	MYSQL* con;

	// ��¼��һ��������Ϣ��id
	unsigned int msg_id = 1;

	DB();
	~DB();
	
	void query(string tablename);  //��ѯ����
	void insert(string tablename);  //�������
	void delet(string tablename);  //ɾ������
	void update(string tablename);  //��������

	bool sql(string sql);  //����sql���(ֻ��1��)
	bool transc1(char* name, char* pswd, unsigned int sex, char* act);  //������1������people�˻���ѡ��actor��ɫ

private:
	MYSQL* connect();  //��������

	string roleOf(string user); //��ѯĳ��user�Ľ�ɫ
	string getTime();  //��ȡϵͳʱ��
	bool CreAcc(char* name, char* pswd, unsigned int sex); //����people���¼�������˻���,preparestatement
	void openAutoCommit();  //�����Զ��ύ����
};