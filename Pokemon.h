#ifndef POKEMON_H
#define POKEMON_H
#include<iostream>
#include <stdlib.h>
#include<stdio.h>
#include<string>
using namespace std;

class Pokemon;

enum Poktype {//宝可梦种类
	ATK,
	HP,
	DEF,
	SPE
};

class Base {//精灵的基类
protected:
	Poktype type;//宝可梦种类
	string name;//宝可梦名字
	int Atk; //力量
	int Def;//防御
	int Hp;//生命
	int Speed;//敏捷
	int expneed[14];		//升级需要的经验
	string skillName[4]; //技能名称
	string skillDscp[4]; //技能描述
	int pp[3];			//技能使用次数
public:
	Base(Poktype);//初始化函数
	string raceName() const { return name; }//返回名字
	Poktype gettype() const { return type; }//返回种族
	int getAtk() const { return Atk; }//返回力量
	int getDef() const { return Def; }//返回防御
	int getHp() const { return Hp; }
	int getSpeed() const { return Speed; }
	string getskillName(int n) const;//返回技能名称
	string getskillDscp(int n) const;
	int getpp(int n) const;
	int getexpneed(int level) const;//返回升级需要的经验
	virtual bool attack(Pokemon &attacker, Pokemon &target, int skillindex = 0) const = 0;//攻击函数，纯虚函数

};

template <int T>
class Race :public Base {//具体的种族
public:
	Race();//具体种族的初始化
	bool attack(Pokemon &attacker, Pokemon &aim, int skillIndex = 0) const;//具体种族的攻击函数
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
	}
};

class Pokemon {//具体的宝可梦
private:
	Base &race;
	int baseatk;//基础数值
	int basedef;
	int basehp;
	int basespe;
	int level;
	int exp;
	int id;//在数据库中的位置
	string name;

	int atk;//战斗中的数值
	int def;
	int hp;
	int spe;
	int pp[3];
public:
	Pokemon(Base &race, const string &name = "");//具体的宝可梦初始化函数	
	int getbatk() { return baseatk; }//获得基础属性
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

	int getatk() { return atk; }//获得战斗状态属性
	int getdef() { return def; }
	int gethp() { return hp; }
	int getspe() { return spe; }
	int getpp(int n) { return pp[n]; }

	bool changehp(int n);//战时改变属性
	void changedef(int n);
	void changespe(int n);
	void changeatk(int n);

	bool gainexp(int n);//获得经验并且升级函数
	bool attack(Pokemon &target);//攻击函数
	void recover();//重置战时属性

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

