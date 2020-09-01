#include"user.h"

sqlite3 *sql = NULL;
const char * path = "F:/Visualstdioc/Pokemon sever/ConsoleApplication2/CONSUMER.db";
vector<string> loginuser;
Race<0> Charmander;
Race<1> Bulbasaur;
Race<2> Squirtle;
Race<3> Pikachu;

void User::getrandpok() {	
	int i = rand() % 4;
	switch (i) {
		case 0:
		{
			Pokemon A(Charmander);
			pok.push_back(A);
			break;
		}
		case 1:
		{
			Pokemon A(Bulbasaur);
			pok.push_back(A);
			break;
		}

		case 2:
		{
			Pokemon A(Squirtle);
			pok.push_back(A);
			break;
		}

		case 3:
		{
			Pokemon A(Pikachu);
			pok.push_back(A);
			break;
		}
	}
	string Sentence = "INSERT INTO consumer(owner,race,name,numbadge,quabadge,level,exp) VALUES('" + name + "','" + pok.back().getracename() + "','" + pok.back().getname() + "',"+"'��','��'," + to_string(pok.back().getlev()) + ", " + to_string(pok.back().getexp()) + ");";        //SQL���
	const char *sqlSentence = &Sentence[0];
	sqlite3_stmt *stmt = NULL;        //stmt�����
	//���в���ǰ��׼����������������Ϸ���
	//-1����ϵͳ���Զ�����SQL���ĳ���
	int result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		cout << "����������OK" << endl;
		//ִ�и����
		sqlite3_step(stmt);
	}
	else {
		cout << "����������������" << endl;
	}
	//�����������׼��ִ����һ�����
	sqlite3_finalize(stmt);
}
void User::readonepok(int id,string race, string name, int level, int exp) {
	int hmexptlev[15] = { 0,5,15,35,70,125,205,315,460,645,875,1155,1490,1885,2345 };
	if (race == "С����") {
		Pokemon A(Charmander,name);
		A.gainexpfs(hmexptlev[level - 1] + exp);
		A.changeid(id);
		pok.push_back(A);
	}
	else if (race == "���ܻ�") {
		Pokemon A(Bulbasaur,name);
		A.gainexpfs(hmexptlev[level - 1] + exp);
		A.changeid(id);
		pok.push_back(A);
	}
	else if (race == "�����") {
		Pokemon A(Squirtle,name);
		A.gainexpfs(hmexptlev[level - 1] + exp);
		A.changeid(id);
		pok.push_back(A);
	}
	else {
		Pokemon A(Pikachu,name);
		A.gainexpfs(hmexptlev[level - 1] + exp);
		A.changeid(id);
		pok.push_back(A);
	}
}
User::User(string user_name) :name(user_name){
	win = 0;
	los = 0;
	numbadge = "��";
	quabadge = "��";			
}

void User::changebadge() {
	if (pok.size() > 5)
		numbadge = "ͭ";
	else if (pok.size() > 10)
		numbadge = "��";
	else if (pok.size() > 15)
		numbadge = "��";
	auto begin = pok.begin(), end = pok.end();
	int num = 0;
	while (begin != end) {
		if ((*begin).getlev() == 15)
			num++;
		begin++;
	}
	if (num > 5)
		quabadge = "ͭ";
	else if (num > 10)
		quabadge = "��";
	else if (num > 15)
		quabadge = "��";
}
