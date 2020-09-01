#include"list.h"
#include"user.h"
List list;
void List::initlist() {
	int hmexptlev[15] = { 0,5,15,35,70,125,205,315,460,645,875,1155,1490,1885,2345 };
	for (int i = 0; i < 15; i++) {//每个等级一个
		int j = rand() % 4;
		switch (j) {
		case 0:
		{
			Pokemon A(Charmander);
			A.gainexpfs(hmexptlev[i]);
			lis.push_back(A);
			break;
		}
		case 1:
		{
			Pokemon A(Bulbasaur);
			A.gainexpfs(hmexptlev[i]);
			lis.push_back(A);
			break;
		}

		case 2:
		{
			Pokemon A(Squirtle);
			A.gainexpfs(hmexptlev[i]);
			lis.push_back(A);
			break;
		}

		case 3:
		{
			Pokemon A(Pikachu);
			A.gainexpfs(hmexptlev[i]);
			lis.push_back(A);
			break;
		}
		}
	}
	for (int i = 0; i < 10; i++) {//随机来10个
		int j = rand() % 4;
		int k = rand() % 15;
		switch (j) {
		case 0:
		{
			Pokemon A(Charmander);
			A.gainexp(hmexptlev[k]);
			lis.push_back(A);
			break;
		}
		case 1:
		{
			Pokemon A(Bulbasaur);
			A.gainexp(hmexptlev[k]);
			lis.push_back(A);
			break;
		}

		case 2:
		{
			Pokemon A(Squirtle);
			A.gainexp(hmexptlev[k]);
			lis.push_back(A);
			break;
		}

		case 3:
		{
			Pokemon A(Pikachu);
			A.gainexp(hmexptlev[k]);
			lis.push_back(A);
			break;
		}
		}
	}
		
}

string List::showlist() {
	string output="精灵列表:\n";
	auto begin = lis.begin(), end = lis.end();
	int i = 0;
	while (begin != end) {		
		output = output + "序列号：" + to_string(i) + " 精灵名：" + (*begin).getname() + " 等级：" + to_string((*begin).getlev())+"\n";
		begin++;
		i++;
	}
	return output;
}

Pokemon& List::findtarget(int order) {
	auto begin = lis.begin(), end = lis.end();
	int i = 0;
	while (begin != end) {
		if (i == order) {
			return *begin;
		}
		i++;
		begin++;
	}

}