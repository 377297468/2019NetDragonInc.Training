#include "mysql.h"
#include <string>
#pragma comment(lib,"libmySQL.lib")
using namespace std;

class DB
{
public:
	char user[20] = "root";
	char passwd[20] = "";
	char ip[20] = "localhost";
	char dbname[20] = "gamedb";
	MYSQL * con;
	unsigned int msg_id = 1;  // ��¼��һ��������Ϣ��id

	~DB();
	MYSQL* connect();  //��������
	void query();  //��ѯ���б��е�����
	void query(string tablename);  //��ѯĳһ�ű��е�����
	void insert(string tablename);  //������ݣ����people�û�����msg�����¼��
	void delet(string tablename);  //ɾ�����ݣ����people�û���
	void update(string tablename);  //�������ݣ����people�û�����actor��ɫ��

	bool sql(string sql);  //����sql���(ֻ��1��)
	bool transc1(char* name, char* pswd, unsigned int sex, char* act);  //������1������people�˻���ѡ��actor��ɫ

private:
	string userOf(string actor); //��ѯĳ��actor��Ӧ��user
	string actorOf(string user); //��ѯĳ��user��Ӧ��actor
	string getTime();  //��ȡϵͳʱ��
	bool CreAcc(char* name, char* pswd, unsigned int sex); //����people���¼�������˻���,preparestatement
	void openAutoCommit();  //�����Զ��ύ����
};
