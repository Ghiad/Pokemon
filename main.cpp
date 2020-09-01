#include"user.h"
#include"list.h"
#include"net.h"
#include<iostream>
#include <algorithm>
using namespace std;
#define MAX_LENGTH 2000

SOCKET connSocket;
int main()
{	
	int result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);
	if (result == SQLITE_OK) {
		cout << "打开数据库连接成功\n";
	}
	else {
		cout << "打开数据库连接失败";		
	}

	//创建表
	const char *sqlSentence = "CREATE TABLE IF NOT EXISTS consumer(id integer PRIMARY KEY AUTOINCREMENT,owner text NOT NULL,race text NOT NULL,name text NOT NULL,level integer,exp integer,win integer,los integer,numbadge text NOT NULL,quabadge text NOT NULL)";
	sqlite3_stmt *stmt = NULL;
	result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		cout << "添加1数据语句OK\n";
		//执行该语句
		sqlite3_step(stmt);

	}
	else {
		cout << "添加1数据语句有问题\n";
	}
	//清理语句句柄，准备执行下一个语句
	sqlite3_finalize(stmt);

	//加载套接字库
	WSADATA wsaData;
	int iRet = 0;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iRet != 0)
	{
		cout << "WSAStartup(MAKEWORD(2, 2), &wsaData) execute failed!" << endl;;
		return -1;
	}
	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
	{
		WSACleanup();
		cout << "WSADATA version is not correct!" << endl;
		return -1;
	}

	//创建套接字
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		cout << "serverSocket = socket(AF_INET, SOCK_STREAM, 0) execute failed!" << endl;
		return -1;
	}

	//初始化服务器地址族变量
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	//绑定
	iRet = bind(serverSocket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (iRet == SOCKET_ERROR)
	{
		cout << "bind(serverSocket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) execute failed!" << endl;
		return -1;
	}


	//监听
	iRet = listen(serverSocket, CONNECT_NUM_MAX);
	if (iRet == SOCKET_ERROR)
	{
		cout << "listen(serverSocket, 10) execute failed!" << endl;
		return -1;
	}

	//等待连接_接收_发送
	SOCKADDR_IN clientAddr;
	int len = sizeof(SOCKADDR);
	list.initlist();
	while (1)
	{
		connSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &len);
		if (connSocket == INVALID_SOCKET)
		{
			cout << "accept(serverSocket, (SOCKADDR*)&clientAddr, &len) execute failed!" << endl;
			return -1;
		}

		char sendBuf[MAX_LENGTH];
		sprintf_s(sendBuf, "Welcome %s", inet_ntoa(clientAddr.sin_addr));
		send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);

		
		while (1) {
			char recvBuf[MAX_LENGTH];
			char sendBuf[MAX_LENGTH];
			memset(sendBuf, 0, MAX_LENGTH);
			memset(recvBuf, 0, MAX_LENGTH);
			string rec;
			sprintf_s(sendBuf, "你可以输入的命令有:\n|注册|登录|登出|查询精灵|查询在线用户|查询胜率|查看勋章|决斗\n你现在可以输入命令了!");
			send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);

			recv(connSocket, recvBuf, MAX_LENGTH, 0);
			printf("%s\n", recvBuf);
			rec = recvBuf;
			if (rec == "注册") {
				sprintf_s(sendBuf, "请输入你所要注册用户的用户名\n");
				send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
				recv(connSocket, recvBuf, MAX_LENGTH, 0);
				rec = recvBuf;

				bool success = false;
				while (!success) {//检查是否有相同用户名
					memset(recvBuf, 0, MAX_LENGTH);
					string Sentence;

					Sentence = "SELECT owner FROM consumer WHERE owner = '" + rec + "'";
					const char *sqlSentence = &Sentence[0];
					sqlite3_stmt *stmt = NULL;
					int result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);

					if (result == SQLITE_OK) {
						cout << "添加2数据语句OK" << endl;
						//执行该语句
						string a;
						while (sqlite3_step(stmt) == SQLITE_ROW) {
							// 取出第1列字段的值
							const unsigned char *name = sqlite3_column_text(stmt, 0);

							a = (const char*)name;
						}
						if (a == rec) {
							sprintf_s(sendBuf, "你输入的用户名已存在，请重新输入\n");
							send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
							recv(connSocket, recvBuf, MAX_LENGTH, 0);
							rec = recvBuf;
						}
						else {
							sprintf_s(sendBuf, "成功注册！\n");
							send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
							success = true;
						}
					}
					else {
						cout << "添加2数据语句有问题" << endl;
					}
					sqlite3_finalize(stmt);
				}
				//清理语句句柄，准备执行下一个语句
				User use(rec);
				for (int j = 0; j < 3; j++) {
					use.getrandpok();
				}
			}
			else if (rec == "登录") {
				
				sprintf_s(sendBuf, "请输入你所要登录用户的用户名\n");
				send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
				recv(connSocket, recvBuf, MAX_LENGTH, 0);
				rec = recvBuf;

				bool success = false;
				while (!success) {//检查是否有相同用户名
					memset(recvBuf, 0, MAX_LENGTH);
					string Sentence;

					Sentence = "SELECT owner FROM consumer WHERE owner = '" + rec + "'";
					const char *sqlSentence = &Sentence[0];
					sqlite3_stmt *stmt = NULL;
					int result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);

					if (result == SQLITE_OK) {
						cout << "添加3数据语句OK" << endl;
						//执行该语句
						string a;
						while (sqlite3_step(stmt) == SQLITE_ROW) {
							// 取出第0列字段的值
							const unsigned char *name = sqlite3_column_text(stmt, 0);
							a = (const char*)name;
						}
						if (a == rec) {
							sprintf_s(sendBuf, "登录成功！\n");
							send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
							loginuser.push_back(rec);
							success = true;
						}
						else {
							sprintf_s(sendBuf, "登录失败，请重新输入\n");
							send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
							recv(connSocket, recvBuf, MAX_LENGTH, 0);
							rec = recvBuf;
						}
					}
					else {
						cout << "添加3数据语句有问题" << endl;
					}
					sqlite3_finalize(stmt);
				}

			}
			else if (rec == "登出") {
				
				sprintf_s(sendBuf, "请选择你要登出的用户\n");
				send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
				recv(connSocket, recvBuf, MAX_LENGTH, 0);
				rec = recvBuf;
				auto success = false;
				while (!success) {
					memset(recvBuf, 0, MAX_LENGTH);
					auto begin = loginuser.begin();
					auto end = loginuser.end();
					bool suc = false;
					while (begin != end) {
						if (rec == (*begin)) {
							loginuser.erase(begin);
							suc = true;
							success = true;
							sprintf_s(sendBuf, "登出成功\n");
							send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
							break;
						}
						begin++;
					}
					if (!suc) {
						sprintf_s(sendBuf, "你要登出的用户并不在线,请重新输入\n");
						send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
						recv(connSocket, recvBuf, MAX_LENGTH, 0);
						rec = recvBuf;
					}
				}

			}
			else if (rec == "查询精灵") {
				
				const char *sqlSentence = "SELECT owner, race, name ,level FROM consumer;";    //SQL语句
				sqlite3_stmt *stmt = NULL;    // stmt语句句柄

				//进行查询前的准备工作——检查语句合法性
				//-1代表系统会自动计算SQL语句的长度
				int result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);

				if (result == SQLITE_OK) {
					cout << "查询语句OK" << endl;
					// 每调一次sqlite3_step()函数，stmt语句句柄就会指向下一条记录
					string output;
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						// 取出第0列字段的值
						const unsigned char *owner = sqlite3_column_text(stmt, 0);
						// 取出第1列字段的值
						const unsigned char *race = sqlite3_column_text(stmt, 1);
						// 取出第2列字段的值
						const unsigned char *name = sqlite3_column_text(stmt, 2);
						int level = sqlite3_column_int(stmt, 3);
						//输出相关查询的数据
						string a = (const char*)owner;
						string b = (const char*)name;
						string c = (const char *)race;
						output = output + "用户名 = " + a + ", 拥有精灵:" + b + " 种族:" + c + " 等级：" + to_string(level) + "\n";
					}
					const char *out = &output[0];
					sprintf_s(sendBuf, out);
					send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
					memset(sendBuf, MAX_LENGTH, 0);
				}
				else {
					std::clog << "查询语句有问题";
				}
				//清理语句句柄，准备执行下一个语句
				sqlite3_finalize(stmt);
			}
			else if (rec == "查询在线用户") {
				
				auto begin = loginuser.begin(), end = loginuser.end();
				string output;
				if (begin == end) {
					output = "当前没有在线的用户!";
				}
				else {
					output = "当前在线的用户有：";
					while (begin != end) {
						output += (*begin) + " ";
						begin++;
					}
					output += "\n";
				}
				const char *out = &output[0];
				sprintf_s(sendBuf, out);
				send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
			}
			else if (rec == "决斗") {
								
				sprintf_s(sendBuf, "请选择你想使用的在线用户\n");
				send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
				recv(connSocket, recvBuf, MAX_LENGTH, 0);
				string attack = recvBuf;
				auto itr = find(loginuser.begin(), loginuser.end(), attack);
				//输入的用户在线
				if (itr != loginuser.end()) {
					User attacker(attack);

					sprintf_s(sendBuf, "请选择你的对战方式：升级赛 or 决斗赛\n");
					send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
					recv(connSocket, recvBuf, MAX_LENGTH, 0);
					rec = recvBuf;
					while (rec != "升级赛"&&rec != "决斗赛") {
						sprintf_s(sendBuf, "选择赛制错误，请重新输入赛制\n");
						send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
						recv(connSocket, recvBuf, MAX_LENGTH, 0);
						rec = recvBuf;
					}

					string output;//打印虚拟精灵列表给客户端
					const char*out;
					output = list.showlist();
					out = &output[0];
					sprintf_s(sendBuf, out);
					send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);

					sprintf_s(sendBuf, "请选择你要对战的精灵序号\n");
					send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
					recv(connSocket, recvBuf, MAX_LENGTH, 0);

					string aim = recvBuf;//找出列表中要对战的精灵
					int tar = atoi(aim.c_str());
					Pokemon target = list.findtarget(tar);

					//挑出用户拥有的精灵
					string Sentence = "SELECT id,race,name,level,exp FROM consumer WHERE owner = '" + attack + "';";
					const char *sqlSentence = &Sentence[0];
					sqlite3_stmt *stmt = NULL;
					int result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);
					if (result == SQLITE_OK) {
						cout << "添加4数据语句OK" << endl;
						//执行该语句
						string a;
						string b;

						while (sqlite3_step(stmt) == SQLITE_ROW) {
							// 取出字段的值
							int id = sqlite3_column_int(stmt, 0);
							const unsigned char *race = sqlite3_column_text(stmt, 1);
							const unsigned char *name = sqlite3_column_text(stmt, 2);
							int level = sqlite3_column_int(stmt, 3);
							int exp = sqlite3_column_int(stmt, 4);

							a = (const char*)race;
							b = (const char*)name;
							attacker.readonepok(id, a, b, level, exp);
						}
					}
					else {
						cout << "添加4数据语句有问题" << endl;
					}
					sqlite3_finalize(stmt);

					//打印用户拥有的精灵给客户端
					output = "你拥有的精灵：\n";
					auto begin = attacker.retpok().begin(), end = attacker.retpok().end();
					int i = 0;
					while (begin != end) {
						output += "序列：" + to_string(i) + " " + (*begin).getname() + " " + to_string((*begin).getlev()) + "级\n";
						begin++;
						i++;
					}

					//从用户拥有的精灵里挑出对战精灵
					output += "请选择你要出战的精灵序列号\n";
					out = &output[0];
					sprintf_s(sendBuf, out);
					send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);

					//决斗开始
					recv(connSocket, recvBuf, MAX_LENGTH, 0);
					aim = recvBuf;
					tar = atoi(aim.c_str());
					Battle war(attacker.retpok(tar), target);
					bool whowin = war.start();//用户赢则为1，反之为0

					sprintf_s(sendBuf, "对战结束\n");
					send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
					Sleep(100);
					int exp = 0;
					if (whowin) {//判断战斗后得到的经验
						if (attacker.retpok(tar).getlev() > target.getlev())
							exp += attacker.retpok(tar).getexp() / 10;
						else
							exp += attacker.retpok(tar).getexp() / 5;
						attacker.changewin();
						if (exp == 0)
							exp = 1;
					}
					else {
						if (attacker.retpok(tar).getlev() > target.getlev())
							exp += 0;
						else
							exp += attacker.retpok(tar).getexp() / 10;
						attacker.changelos();
					}				
					attacker.retpok(tar).gainexp(exp);

					Sentence = "UPDATE consumer SET win = " + to_string(attacker.getwin()) + ", los = " + to_string(attacker.getlos()) + " WHERE owner = '" + attacker.getname() + "';";
					sqlSentence = &Sentence[0];
					stmt = NULL;
					result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);
					if (result == SQLITE_OK) {
						cout << "添加5数据语句OK" << endl;
						//执行该语句
						sqlite3_step(stmt);
					}
					else {
						cout << "添加5数据语句有问题" << endl;
					}
					//清理语句句柄，准备执行下一个语句
					sqlite3_finalize(stmt);

					Sentence = "UPDATE consumer SET level = " + to_string(attacker.retpok(tar).getlev()) + ", exp = " + to_string(attacker.retpok(tar).getexp()) + " WHERE id = " + to_string(attacker.retpok(tar).getid()) + ";";
					sqlSentence = &Sentence[0];
					stmt = NULL;
					result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);
					if (result == SQLITE_OK) {
						cout << "添加6数据语句OK" << endl;
						//执行该语句
						sqlite3_step(stmt);
					}
					else {
						cout << "添加6数据语句有问题" << endl;
					}
					//清理语句句柄，准备执行下一个语句
					sqlite3_finalize(stmt);

					if (rec == "决斗赛") {
						if (whowin) {//胜利获得精灵
							attacker.getpok(target);
							Sentence = "INSERT INTO consumer(owner,race,name,numbadge,quabadge,level,exp) VALUES('" + attacker.getname() + "','" + target.getracename() + "','" + target.getname() + "'," + "'无','无',"+to_string(target.getlev()) + ", " + to_string(target.getexp()) + ");";
							sqlSentence = &Sentence[0];
							stmt = NULL;
							result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);
							if (result == SQLITE_OK) {
								cout << "添加7数据语句OK" << endl;
								//执行该语句
								sqlite3_step(stmt);
							}
							else {
								cout << "添加7数据语句有问题" << endl;
							}
							//清理语句句柄，准备执行下一个语句
							sqlite3_finalize(stmt);
							output = attacker.getname() + "获得了精灵:" + target.getname() + "\n";
							out = &output[0];
							sprintf_s(sendBuf, out);
							send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
						}
						else {//失败失去精灵
							auto begin = attacker.retpok().begin(), end = attacker.retpok().end();
							for (int j = 0; begin != end; begin++, j++) {
								if (j == tar) {

									Sentence = "DELETE FROM consumer WHERE id = " + to_string((*begin).getid()) + ";";
									sqlSentence = &Sentence[0];
									stmt = NULL;
									result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);
									if (result == SQLITE_OK) {
										cout << "添加8数据语句OK" << endl;
										//执行该语句
										sqlite3_step(stmt);
									}
									else {
										cout << "添加8数据语句有问题" << endl;
									}
									//清理语句句柄，准备执行下一个语句
									sqlite3_finalize(stmt);
									output = attacker.getname() + "失去了精灵:" + target.getname() + "\n";
									out = &output[0];
									sprintf_s(sendBuf, out);
									send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
									attacker.retpok().erase(begin);

									break;
								}
							}
						}
					}
					if (attacker.retpok().begin() == attacker.retpok().end()) {//没有精灵了，随机给一个
						attacker.getrandpok();
					}
					attacker.changebadge();
					Sentence = "UPDATE consumer SET numbadge = '" + attacker.getnumbadge() + "', quabadge = '" + attacker.getquabadge() + "' WHERE owner = '" + attacker.getname() + "';";
					sqlSentence = &Sentence[0];
					stmt = NULL;
					result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);
					if (result == SQLITE_OK) {
						cout << "添加9数据语句OK" << endl;
						//执行该语句
						sqlite3_step(stmt);
					}
					else {
						cout << "添加9数据语句有问题" << endl;
					}
					//清理语句句柄，准备执行下一个语句
					sqlite3_finalize(stmt);

				}
				else {
					sprintf_s(sendBuf, "你选择的用户不在线\n");
					send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
				}
			}
			else if (rec == "查询胜率") {
				
				sprintf_s(sendBuf, "请输入你想查看的用户名");
				send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
				recv(connSocket, recvBuf, MAX_LENGTH, 0);
				rec = recvBuf;
				string Sentence = "SELECT win, los FROM consumer WHERE owner = '" + rec + "';";
				const char *sqlSentence = &Sentence[0];    //SQL语句
				sqlite3_stmt *stmt = NULL;    // stmt语句句柄
				//进行查询前的准备工作——检查语句合法性
				//-1代表系统会自动计算SQL语句的长度
				int result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);

				if (result == SQLITE_OK) {
					cout << "查询语句OK" << endl;
					// 每调一次sqlite3_step()函数，stmt语句句柄就会指向下一条记录
					string output = "该用户的胜率：";
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						// 取出第0列字段的值
						int win = sqlite3_column_int(stmt, 0);
						// 取出第1列字段的值
						int los = sqlite3_column_int(stmt, 1);
						//输出相关查询的数据
						double pop;
						if (win == 0 && los == 0)
							pop = 0;
						else
							pop = (double)win / (win + los); 
						output = output + to_string(pop) + "\n";
					}
					const char *out = &output[0];
					sprintf_s(sendBuf, out);
					send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
					memset(sendBuf, MAX_LENGTH, 0);
				}
				else {
					std::clog << "查询语句有问题";
				}
				//清理语句句柄，准备执行下一个语句
				sqlite3_finalize(stmt);
			}
			else if (rec == "查询勋章") {
				
				sprintf_s(sendBuf, "请输入你想查看的用户名");
				send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
				recv(connSocket, recvBuf, MAX_LENGTH, 0);
				rec = recvBuf;
				string Sentence = "SELECT sumbadge, quabadge FROM consumer WHERE owner = '" + rec + "';";
				const char *sqlSentence = &Sentence[0];    //SQL语句
				sqlite3_stmt *stmt = NULL;    // stmt语句句柄
				//进行查询前的准备工作——检查语句合法性
				//-1代表系统会自动计算SQL语句的长度
				int result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);

				if (result == SQLITE_OK) {
					cout << "查询语句OK" << endl;
					// 每调一次sqlite3_step()函数，stmt语句句柄就会指向下一条记录
					string output = "该用户宠物个数勋章：";
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						// 取出第0列字段的值
						const unsigned char *sumbadge = sqlite3_column_text(stmt, 0);
						// 取出第1列字段的值
						const unsigned char *quabadge = sqlite3_column_text(stmt, 1);
						//输出相关查询的数据
						string a = (const char*)sumbadge;
						string b = (const char*)quabadge;
						output = output + a + ", 高级宠物勋章:" + b + "\n";
					}
					const char *out = &output[0];
					sprintf_s(sendBuf, out);
					send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
					memset(sendBuf, MAX_LENGTH, 0);
				}
				else {
					sprintf_s(sendBuf, "未知命令，请重新输入\n");
					send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
				}
			}
			else {
			
				sprintf_s(sendBuf, "未知命令,请重新输入\n");
				send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
			}
		}
		closesocket(connSocket);
	}
	system("pause");
	return 0;
}