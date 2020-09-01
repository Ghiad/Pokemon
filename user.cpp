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
	string Sentence = "INSERT INTO consumer(owner,race,name,numbadge,quabadge,level,exp) VALUES('" + name + "','" + pok.back().getracename() + "','" + pok.back().getname() + "',"+"'无','无'," + to_string(pok.back().getlev()) + ", " + to_string(pok.back().getexp()) + ");";        //SQL语句
	const char *sqlSentence = &Sentence[0];
	sqlite3_stmt *stmt = NULL;        //stmt语句句柄
	//进行插入前的准备工作——检查语句合法性
	//-1代表系统会自动计算SQL语句的长度
	int result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		cout << "添加数据语句OK" << endl;
		//执行该语句
		sqlite3_step(stmt);
	}
	else {
		cout << "添加数据语句有问题" << endl;
	}
	//清理语句句柄，准备执行下一个语句
	sqlite3_finalize(stmt);
}
void User::readonepok(int id,string race, string name, int level, int exp) {
	int hmexptlev[15] = { 0,5,15,35,70,125,205,315,460,645,875,1155,1490,1885,2345 };
	if (race == "小火龙") {
		Pokemon A(Charmander,name);
		A.gainexpfs(hmexptlev[level - 1] + exp);
		A.changeid(id);
		pok.push_back(A);
	}
	else if (race == "妙蛙花") {
		Pokemon A(Bulbasaur,name);
		A.gainexpfs(hmexptlev[level - 1] + exp);
		A.changeid(id);
		pok.push_back(A);
	}
	else if (race == "杰尼龟") {
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
	numbadge = "无";
	quabadge = "无";			
}

void User::changebadge() {
	if (pok.size() > 5)
		numbadge = "铜";
	else if (pok.size() > 10)
		numbadge = "银";
	else if (pok.size() > 15)
		numbadge = "金";
	auto begin = pok.begin(), end = pok.end();
	int num = 0;
	while (begin != end) {
		if ((*begin).getlev() == 15)
			num++;
		begin++;
	}
	if (num > 5)
		quabadge = "铜";
	else if (num > 10)
		quabadge = "银";
	else if (num > 15)
		quabadge = "金";
}
