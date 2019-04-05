#include <iostream>
using namespace std;
#include"crole.h"

CRole::CRole(int headPic, int hp, int atk, int def, int exp, int lv)
	:m_headPic(headPic), m_hp(hp), m_atk(atk), m_def(def), m_exp(exp), m_lv(lv)
{
}

CRole::~CRole()
{
}

int CRole::attack()
{
	return m_atk;
}

void CRole::jump()
{
	cout << "����������˹���" << endl;
}

int CRole::getHp() const
{
	return m_hp;
}

void CRole::beAttack(int damage)
{
	m_hp -= damage;
}
//ս����ʼǰ��׼��
void CRole::perpare()
{
	m_hp = 100 * m_lv;
	m_atk = 10 * m_lv;
	m_def = 10 * m_lv;
	if (m_headPic == HEROHEAD)
		cout << "��ɫ��Ӣ��" << endl;
	else if (m_headPic == ENEMYHEAD)
	{
		cout << "vs" << endl;
		cout << "��ɫ������" << endl;
	}
	cout << "�ȼ�:" << m_lv << endl;
	cout << "����ֵ:" << m_hp << endl;
	cout << "������:" << m_atk << endl;
	cout << "������:" << m_def << endl;
}