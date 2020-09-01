#ifndef POKEMON_H
#define POKEMON_H
#include<iostream>
#include <stdlib.h>
#include<stdio.h>
#include<string>
#include"net.h"
#define MAX 2000
using namespace std;

class Pokemon;

enum Poktype {//����������
	ATK,
	HP,
	DEF,
	SPE
};

class Base {//����Ļ���
protected:
	Poktype type;//����������
	string name;//����������
	int Atk; //����
	int Def;//����
	int Hp;//����
	int Speed;//����
	int expneed[14];		//������Ҫ�ľ���
	string skillName[4]; //��������
	string skillDscp[4]; //��������
	int pp[3];			//����ʹ�ô���
public:
	Base(Poktype);//��ʼ������
	string raceName() const { return name; }//��������
	Poktype gettype() const { return type; }//��������
	int getAtk() const { return Atk; }//��������
	int getDef() const { return Def; }//���ط���
	int getHp() const { return Hp; }
	int getSpeed() const { return Speed; }
	string getskillName(int n) const;//���ؼ�������
	string getskillDscp(int n) const;
	int getpp(int n) const;
	int getexpneed(int level) const;//����������Ҫ�ľ���
	virtual bool attack(Pokemon &attacker, Pokemon &target, int skillindex = 0) const = 0;//�������������麯��
	bool dodge(int, int)const;
	bool boot(int, int)const;
};

template <int T>
class Race :public Base {//���������
public:
	Race();//��������ĳ�ʼ��
	bool attack(Pokemon &attacker, Pokemon &aim, int skillIndex = 0) const;//��������Ĺ�������
	Race& operator=(const Race& a) {
		type = a.type;
		name = a.name; Atk = a.Atk;
		Def = a.Def;
		Hp = a.Hp;
		Speed = a.Speed;
		for (int i = 0; i < 14; i++) {
			expneed[i] = a.expneed;
		}
		for (int i = 0; i < 4; i++) {
			skillName[i] = a.skillName[i];
			skillDscp[i] = a.skillDscp[i];			
		}		
		for (int i = 0; i < 3; i++) {
			pp[i] = a.pp[i];
		}
		return *this;
	}
};

class Pokemon {//����ı�����
private:
	Base &race;
	int baseatk;//������ֵ
	int basedef;
	int basehp;
	int basespe;
	int level;
	int exp;
	int id;//�����ݿ��е�λ��
	string name;

	int atk;//ս���е���ֵ
	int def;
	int hp;
	int spe;
	int pp[3];
public:
	Pokemon(Base &race, const string &name = "");//����ı����γ�ʼ������	
	int getbatk() { return baseatk; }//��û�������
	int getbdef() { return basedef; }
	int getbhp() { return basehp; }
	int getbspe() { return basespe; }
	int getlev() { return level; }
	int getexp() { return exp; }
	int getid() { return id; }
	int changeid(int n) { return id = n; }
	string getname() { return name; }
	string getracename() { return race.raceName(); }
	string getracetype() const;
	string skillName(int n) const { return race.getskillName(n); }
	string skillDscp(int n) const { return race.getskillDscp(n); }
	int basepp(int i) const { return race.getpp(i); }

	int getatk() { return atk; }//���ս��״̬����
	int getdef() { return def; }
	int gethp() { return hp; }
	int getspe() { return spe; }
	int getpp(int n) { return pp[n]; }

	bool changehp(int n);//սʱ�ı�����
	void changedef(int n);
	void changespe(int n);
	void changeatk(int n);

	bool gainexp(int n);//��þ��鲢����������
	bool gainexpfs(int n);//��þ��鲢����������,���ڷ������˳�ʼ��
	bool attack(Pokemon &target);//��������
	void recover();//����սʱ����

	Pokemon& operator=(const Pokemon& a) {
		race = a.race;
		baseatk = a.baseatk;
		basedef = a.basedef;
		basehp = a.basehp;
		basespe = a.basespe;
		level = a.level;
		exp = a.exp;
		id = a.id;
		name = a.name;
		atk = a.atk;
		def = a.def;
		hp = a.hp;
		spe = a.spe;
		for (int i = 0; i < 3; i++)
			pp[i] = a.pp[i];
		return *this;
	}
};

class Battle {
private:
	Pokemon &pokA, pokB;
	int timerA;
	int timerB;
public:
	Battle(Pokemon &pok1, Pokemon &pok2) :pokA(pok1), pokB(pok2) {}
	bool start();
};
#endif // !POKEMON_H

