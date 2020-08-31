#ifndef BATTLE_H
#define BATTLE_H
#include<string>
#include<vector>
#include<iostream>
#include<cstdio>
#include"Pokemon.h"

extern vector<Pokemon> list;
void initlist(vector<Pokemon>&);
string showlist(vector<Pokemon>);
Pokemon findtarget(int i);
void addpokmon(vector<Pokemon>&,string,string,int,int);
#endif // !BATTLE_H
