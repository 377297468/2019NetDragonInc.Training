#include <iostream>
using namespace std;
#include"cenemy.h"

CEnemy::CEnemy(int headPic, int hp, int atk, int def, int exp, int lv)
	:CRole(headPic, hp, atk, def, exp, lv)
{
}

CEnemy::~CEnemy()
{
}

int CEnemy::palmAttack()
{
	cout << "����ʹ��������,��Ӣ�������" << m_atk * 2 << "���˺�" << endl;
	return m_atk * 2;
}

int CEnemy::serialKick()
{
	cout << "����ʹ����������,��Ӣ�������" << m_atk * 3 << "���˺�" << endl;
	return m_atk * 3;
}
