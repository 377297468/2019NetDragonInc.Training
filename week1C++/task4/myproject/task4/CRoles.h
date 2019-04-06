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
	int BaoJi;   //������
	int expNeedNext; //������������ľ�������
	Weapon* weapon;  //���е�����
	bool jumping;  //�Ƿ�����Ծ��
	int skillATK;  //���ܸ��ӵĹ�����,����Ϊ��

	CRole();
	CRole(string hi, int a, int d);
	~CRole();

	void atkWeapon(CRole& role,int seed);  //�չ����л��ᱩ��
	void jump();  //��Ծ���Զ���չ��ͼ���1�˺�
	void jumpEnd();  //������Ծ
	void getWeapon(Weapon& wp);  //�������������������������
	inline void coutAtkDef() { //�����������������
		cout << headIcon << " ---- ATK " << ATK << " ---- DEF " << DEF << " ---- Bao " << BaoJi << "%" << endl;
	}
	void getExp(int exp);  //��ȡ����

protected:
	int EXP;            //ӵ�е��ܾ���
	const int O_LV = 1;     //��ʼ�ȼ�
	const int MAX_LV = 15;  //��ߵȼ�
	int EXP_NEED(int lv);  //����lv�������ܾ���
	inline int expNeedWhenLv(int lv) { //��lv��ʱ����һ�����辭��
		return lv * lv * 10 + 140;
	}
};

class CEnemy; // ǰ������

///////////////////////////////////////
// Ӣ����CHero
// ����1�߶�̶��˺�
// ����2���˺�������
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
// ������CEnemy
// ����1�߶�̶��˺�
// ����2���˺�������
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