#include"battle.h"

vector<Pokemon> list;
void initlist(vector<Pokemon> &target) {
	int hmexptlev[15] = { 0,5,15,35,70,125,205,315,460,645,875,1155,1490,1885,2345 };
	Race<0> Charmander;
	Race<1> Bulbasaur;
	Race<2> Squirtle;
	Race<3> Pikachu;
	for (int i = 0; i < 20; i++) {
		int j = rand() % 4;
		int k = rand() % 15;
		switch (j) {
			case 0:
			{
				Pokemon A(Charmander);
				A.gainexp(hmexptlev[k]);
				target.push_back(A);
				break;
			}
			case 1:
			{
				Pokemon A(Bulbasaur);
				A.gainexp(hmexptlev[k]);
				target.push_back(A);
				break;
			}

			case 2:
			{
				Pokemon A(Squirtle);
				A.gainexp(hmexptlev[k]);
				target.push_back(A);
				break;
			}

			case 3:
			{
				Pokemon A(Pikachu);
				A.gainexp(hmexptlev[k]);
				target.push_back(A);
				break;
			}
		}
	}
}
void addpokmon(vector<Pokemon> target,string race,string name,int level,int exp) {
	int hmexptlev[15] = { 0,5,15,35,70,125,205,315,460,645,875,1155,1490,1885,2345 };
	Race<0> Charmander;
	Race<1> Bulbasaur;
	Race<2> Squirtle;
	Race<3> Pikachu;
	if (race == "С����") {
		Pokemon A(Charmander);
		A.gainexp(hmexptlev[level-1]+exp);
		target.push_back(A);
	}
	else if (race == "���ܻ�") {
		Pokemon A(Bulbasaur);
		A.gainexp(hmexptlev[level - 1] + exp);
		target.push_back(A);
	}
	else if (race == "�����") {
		Pokemon A(Squirtle);
		A.gainexp(hmexptlev[level - 1] + exp);
		target.push_back(A);
	}
	else {
		Pokemon A(Pikachu);
		A.gainexp(hmexptlev[level - 1] + exp);
		target.push_back(A);
	}
}
string showlist(vector<Pokemon> target) {
	string output="�����б�:\n";
	auto begin = target.begin(), end = target.end();
	int i = 0;
	while (begin != end) {		
		output = output + "���кţ�" + to_string(1) + " ��������" + (*begin).getname() + " �ȼ���" + to_string((*begin).getlev());
		begin++;
		i++;
	}
	return output;
}

Pokemon findtarget(int order) {
	auto begin = list.begin(), end = list.end();
	int i = 0;
	while (begin != end) {
		if (i == order) {
			return *begin;
		}
		i++;
		begin++;
	}

}