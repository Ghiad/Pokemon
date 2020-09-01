#ifndef BATTLE_H
#define BATTLE_H
#include<string>
#include<vector>
#include<iostream>
#include<cstdio>
#include"Pokemon.h"

class List {
private:
	vector<Pokemon> lis;
public:
	vector<Pokemon> getlis() { return lis; }
	void initlist();
	string showlist();
	Pokemon& findtarget(int);
};
extern List list;
#endif // !BATTLE_H
