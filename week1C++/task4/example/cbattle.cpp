#include <iostream>
using namespace std;
#include<cstdlib>
#include<ctime>
#include "cbattle.h"

CBattle::CBattle()
{
	cout << "ս��׼��" << endl;
}

CBattle::~CBattle()
{
}
void CBattle::fight(CHero &hero, CEnemy &enemy)
{
	char control;
	while (1)
	{
		hero.perpare();
		enemy.perpare();
		while (1)
		{
			srand((unsigned)time(NULL) + rand() % 6);//���������
			switch (rand() % 6)
			{

			case 0:
				if (rand() % 4 == 0)
				{
					cout << "Ӣ�۶Ե���ʹ������ͨ����������";
					enemy.jump();
					break;
				}
				enemy.beAttack(hero.attack());
				cout << "Ӣ�۶Ե���ʹ������ͨ�����������" << hero.attack() << "���˺�" << endl;
				break;
			case 1:
				if (rand() % 4 == 0)
				{
					cout << "���˶�Ӣ��ʹ������ͨ������Ӣ��";
					hero.jump();
					break;
				}
				cout << "���˶�Ӣ��ʹ������ͨ�����������" << enemy.attack() << "���˺�" << endl;
				hero.beAttack(enemy.attack());
				break;
				
			case 2:
				if (rand() % 4 == 0)
				{
					cout << "Ӣ��ʹ���˱�ˤ,����";
					enemy.jump();
					break;
				}
				enemy.beAttack(hero.hugFall());
				break;
			case 3:
				if (rand() % 4 == 0)
				{
					cout << "����ʹ��������,Ӣ��";
					hero.jump();
					break;
				}
				hero.beAttack(enemy.palmAttack());
				break;
			case 4:
				if (rand() % 4 == 0)
				{
					cout << "Ӣ��ʹ��������,����";
					hero.jump();
					break;
				}
				enemy.beAttack(hero.kick());
				break;
			case 5:
				if (rand() % 4 == 0)
				{
					cout << "����ʹ����������,Ӣ��";
					hero.jump();
					break;
				}
				hero.beAttack(enemy.serialKick());
				break;
			default:
				break;
			}
			if (enemy.getHp() <= 0)
			{
				cout << "hero win" << endl;
				hero.setExp(hero.getExp() + 50 * hero.getLv());
				enemy.setLv(hero.getLv());
				break;
			}
			if (hero.getHp() <= 0)
			{
				cout << "enemy win" << endl;
				break;
			}
		}
		cout << "����c��ʼ��һ�֣�����q�˳�" << endl;
		while (1)
		{
			control = getchar();
			if (control == 'c')
				break;
			else if (control == 'q')
				return ;
		}
	}
}
