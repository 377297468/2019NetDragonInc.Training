#include "CString.h"
CNString::CNString()
{
	m_p = NULL;
}
CNString::CNString(const char *myp)
{
	m_len = strlen(myp);
	m_p = new char[m_len + 1];
	strcpy(m_p, myp);
}
CNString::CNString(const CNString& obj1)
{
	m_len = obj1.m_len;
	m_p = new char[m_len + 1];
	strcpy(m_p, obj1.m_p);
}
void CNString::Show()
{
	for (int i = 0; i < m_len; i++)
	{
		cout << m_p[i];
	}
	cout << endl;
}
CNString::~CNString()
{
	if (m_p != NULL)
	{
		delete[] m_p;
		m_len = 0;
	}
}
// "+"���������
CNString operator+(CNString &obj1, CNString &obj2)
{
	CNString tmp;//�Ǿ�̬�ֲ�������������ջ��������ִ����Ϻ�ᱻ����
	tmp.m_len = obj1.m_len + obj2.m_len;
	tmp.m_p = new char[tmp.m_len + 1];
	strcpy(tmp.m_p, obj1.m_p);
	strcat(tmp.m_p, obj2.m_p);
	return tmp;
}
// ">"���������
bool operator>(CNString &obj1, CNString &obj2)
{
	if (strcmp(obj1.m_p, obj2.m_p)>0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// "<"���������
bool operator<(CNString &obj1, CNString &obj2)
{
	if (strcmp(obj1.m_p, obj2.m_p)<0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// "=="���������
bool operator==(CNString &obj1, CNString &obj2)
{
	if (strcmp(obj1.m_p, obj2.m_p) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}