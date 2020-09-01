#ifndef POKEMON_H
#define POKEMON_H
#include<iostream>
#include <stdlib.h>
#include<stdio.h>
#include<string>
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

};

template <int T>
class Race :public Base {//���������
public:
	Race();//��������ĳ�ʼ��
	bool attack(Pokemon &attacker, Pokemon &aim, int skillIndex = 0) const;//��������Ĺ�������
};

class Pokemon {//����ı�����
private:
	const Base &race;
	int baseatk;//������ֵ
	int basedef;
	int basehp;
	int basespe;
	int level;
	int exp;
	string name;

	int atk;//ս���е���ֵ
	int def;
	int hp;
	int spe;
	int pp[3];
public:
	Pokemon(const Base &race, const string &name = "");//����ı����γ�ʼ������

	int getbatk() { return baseatk; }//��û�������
	int getbdef() { return basedef; }
	int getbhp() { return basehp; }
	int getbspe() { return basespe; }
	int getlev() { return level; }
	int getexp() { return exp; }
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
	bool attack(Pokemon &target);//��������
	void recover();//����սʱ����
};

class Battle {
	private:
		Pokemon &pokA,pokB;
		int timerA;
		int timerB;
	public:
		Battle(Pokemon &pok1, Pokemon &pok2) :pokA(pok1), pokB(pok2) {}
		void start();
};
#endif // !POKEMON_H

