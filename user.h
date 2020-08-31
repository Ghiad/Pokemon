#ifndef USER_H
#define USER_H
#include"Pokemon.h"
#include<string>
#include<vector>
#include<fstream>
#include"sqlite3.h"
class User {
	private:
		string name;//�û���
		vector<Pokemon> pok;//ӵ�еľ���
		int win;//ʤ��
		int los;//�ܳ�
		string numbadge;//�����������
		string quabadge;//�߼��������
	public:
		User(string name);
		vector<Pokemon>& retpok() { return pok; }
		Pokemon& retpok(int order) { return pok[order]; }
		string getname() { return name; }
		int getwin() { return win; }
		void changewin() { win++; }
		int getlos() { return los; }
		void changelos() { los++; }
		double probably() { return (double)getwin() / getlos(); }
		string getnumbadge() { return numbadge; }
		string getquabadge() { return quabadge; }
		void changebadge();
		void getrandpok();
		void readonepok(int,string, string, int, int);
		void getpok(Pokemon target) { pok.push_back(target); }
		//void restorpok(vector<Pokemon> target) { pok = target; }
};

extern sqlite3 *sql;
extern const char *path;
extern vector<string> loginuser;
extern Race<0> Charmander;
extern Race<1> Bulbasaur;
extern Race<2> Squirtle;
extern Race<3> Pikachu;
#endif // !SEVER_H
