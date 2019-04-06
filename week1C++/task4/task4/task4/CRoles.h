#include <string>

using namespace std;

#ifndef _CROLES_
#define _CROLES_

//////////////////////////////////////////
// ȫ�ֳ���
//////////////////////////////////////////
const int O_BAOJI = 25;  //����������25%
const int EXP_ADD = 300;  //ÿӮһ�����þ���

////////////////////////////////
// Weapon��
////////////////////////////////
class Weapon
{
public:
	string name;
	int ATK;    //����ɫ���ӵĶ��⹥����
	int BaoJi;  //������,0��100�������˺�Ĭ��Ϊԭ�˺���2��
	inline Weapon(string n, int atk, int bjl) {
		name = n;
		ATK = atk;
		BaoJi = bjl;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////
// ��ɫ��CRoleΪ���ࣺ
// ��Ա������ͷ��HP��Ѫ������ATK������������DEF������������Lv���ȼ�����EXP������ֵ��
// ��Ա������������������Ծ��
//////////////////////////////////////////////////////////////////////////////////////////
class CRole
{
public:
	string headIcon;  //ͷ��/����
	int HP;
	int ATK;
	int DEF;
	int Lv;
	int EXP;
	int BaoJi;   //������
	const int O_LV = 1;     //��ʼ�ȼ�
	const int MAX_LV = 15;  //��ߵȼ�
	inline int EXP_NEED() { return Lv * Lv * 50; }  //ÿ��һ�����辭��
	Weapon* weapon;  //���е�����
	bool jumping;  //�Ƿ�����Ծ��
	int skillATK;  //���ܸ��ӵĹ�����,����Ϊ��

	CRole();
	CRole(string hi, int a, int d);
	~CRole();

	void atkWeapon(int seed);  //��������ʱ�����2��
	void jump();  //��Ծ����ʱ��Ϊ1�룬���Զ��1s�ļ��ܣ������ȡ����ƣ����˺���
	void jumpEnd();  //������Ծ
	void getWeapon(Weapon& wp);  //�������������������������
	inline void coutAtkDef() { //�����������������
		cout << headIcon << " ---- ATK " << ATK << " ---- DEF " << DEF << " ---- Bao " << BaoJi << "%" << endl;
	}
};

class CEnemy; // ǰ������

///////////////////////////////////////
// Ӣ����CHero
///////////////////////////////////////
class CHero : public CRole
{
public:
	CHero(string headicon, int atk, int def);
	~CHero();
	int skill_kick(CEnemy& enemy);//���ؼ��ܵĳ���ʱ�䣨�룩
	int skill_hug(CEnemy& enemy);
};

////////////////////////////////////////
//������CEnemy�̳���CRole��
////////////////////////////////////////
class CEnemy : public CRole
{
public:
	CEnemy(string headicon, int atk, int def);
	~CEnemy();
	int skill_hand(CHero& hero);
	int skill_kicks(CHero& hero);
};

#endif