#include <iostream>
using namespace std;
#include"chero.h"

CHero::CHero(int headPic, int hp, int atk, int def, int exp, int lv)
	:CRole(headPic, hp, atk, def, exp, lv)
{
}

CHero::~CHero()
{
}

int CHero::kick()
{
	cout << "Ӣ��ʹ��������,�Ե��������" << m_atk * 2 << "���˺�" << endl;
	return m_atk * 2;
}

int CHero::hugFall()
{
	cout << "Ӣ��ʹ���˱�ˤ,�Ե��������" << m_atk * 3 << "���˺�" << endl;
	return m_atk * 3;
}
void CHero::setExp(int exp)
{
	m_exp = exp;
	if (m_exp > m_lv * 100)
	{
		m_exp = 0;
		setLv(getLv() + 1);
		cout << "��������,��ǰ�ȼ�" << getLv() << endl;
	}
}
