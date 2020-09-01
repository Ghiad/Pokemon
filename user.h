#ifndef USER_H
#define USER_H
#include"Pokemon.h"
#include<string>
#include<vector>
#include<fstream>
#include"sqlite3.h"
class User {
	private:
		string name;//用户名
		vector<Pokemon> pok;//拥有的精灵
		int win;//胜场
		int los;//败场
		string numbadge;//宠物个数徽章
		string quabadge;//高级宠物徽章
	public:
		User(string name);

		vector<Pokemon>& retpok() { return pok; }//获得基础属性
		Pokemon& retpok(int order) { return pok[order]; }
		string getname() { return name; }
		int getwin() { return win; }
		void changewin() { win++; }
		int getlos() { return los; }
		void changelos() { los++; }
		double probably() { return (double)getwin() / getlos(); }//计算用户胜率
		string getnumbadge() { return numbadge; }
		string getquabadge() { return quabadge; }
		void changebadge();

		void getrandpok();//随机获得一个精灵
		void readonepok(int,string, string, int, int);//获得一个指定精灵
		void getpok(Pokemon target) { pok.push_back(target); }//获得一个指定精灵
		void restorpok(vector<Pokemon> target) { pok = target; }//将pok重置为target
};

extern sqlite3 *sql;
extern const char *path;
extern vector<string> loginuser;
extern Race<0> Charmander;
extern Race<1> Bulbasaur;
extern Race<2> Squirtle;
extern Race<3> Pikachu;
#endif // !SEVER_H
