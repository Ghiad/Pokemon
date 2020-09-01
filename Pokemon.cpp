#include"Pokemon.h"
string output;
char sendBuf[MAX];
const char* out;
Base::Base(Poktype typ) {
	type = typ;

	Atk = 10;
	Def = 5;
	Hp = 25;
	Speed = 10;

	switch (typ) //不同种族开始的属性不同
	{
	case ATK:
		Atk += 5;
		break;
	case DEF:
		Def += 3;
		break;
	case HP:
		Hp += 10;
		break;
	case SPE:
		Speed += 5;
		break;
	default:
		break;
	}
}

bool Base::dodge(int speed1, int speed2) const {
	int i = rand() % 10;
	if (speed1 < speed2) {
		if (i <= 2)
			return true;
	}
	if (speed1 >= speed2) {
		if (i == 0 )
			return true;
	}
	return false;
}
bool Base::boot(int speed1, int speed2)const {
	int i = rand() % 10;
	if (speed1 < speed2) {
		if (i == 0)
			return true;
	}
	if (speed1 >= speed2) {
		if (i <= 2)
			return true;
	}
	return false;
}
string Base::getskillName(int n) const {
	if (n >= 0 && n <= 3) {
		return skillName[n];
	}
	return "";
}

string Base::getskillDscp(int n)const {
	if (n >= 0 && n <= 3) {
		return skillDscp[n];
	}
	return "";
}

int Base::getpp(int n) const {
	if (n >= 0 && n <= 2) {
		return pp[n];
	}
	return 0;
}

int Base::getexpneed(int level) const {
	if (level >= 2 && level <= 15)
	{
		return expneed[level - 2];
	}
	return 0;
}

template <>
Race<0>::Race() : Base(ATK)//ATK种族的初始化
{
	name = "小火龙";
	expneed[0] = 5;
	for (int i = 1; i < 14; ++i)//初始化经验曲线
	{
		expneed[i] = expneed[i - 1] + 5 * i;
	}
	skillName[0] = "抓";
	skillName[1] = "叫声";
	skillName[2] = "龙息";
	skillName[3] = "喷射火焰";
	skillDscp[0] = "基础攻击";
	skillDscp[1] = "降低攻击力";
	skillDscp[2] = "将强烈的气息吹向对手";
	skillDscp[3] = "向对手发射烈焰";
	pp[0] = 10;
	pp[1] = 5;
	pp[2] = 5;
}
template <>
bool Race<0>::attack(Pokemon &attack, Pokemon &target, int skillindex) const {//高力量型种族的攻击函数
	if (dodge(attack.getspe(), target.getspe())) {
		output += attack.getname() + "的攻击被躲掉了\n";
		return false;
	}
	bool crits = boot(attack.getspe(), target.getspe());
	int damage;
	if (crits) {
		output += "\n"+attack.getname() + "对" + target.getname() + "使用了" + attack.skillName(skillindex) + ",造成了暴击！！！\n";
		//cout << attack.getname() << "对" << target.getname() << "使用了" << attack.skillName(skillindex) << endl;
		if (skillindex == 1) {//不同技能造成的效果不同
			target.changeatk(-target.getatk() / 8);
		}
		else if (skillindex == 2) {
			damage = (attack.getatk() - target.getdef()) * 3;
			return target.changehp(-damage);
		}
		else if (skillindex == 3) {
			int damage = (attack.getatk() - target.getdef()) * 4;
			return target.changehp(-damage);
		}
		else {
			int damage = (attack.getatk() - target.getdef())*2;
			return target.changehp(-damage);
		}
	}
	else {
		output += "\n" + attack.getname() + "对" + target.getname() + "使用了" + attack.skillName(skillindex) + "\n";
		//cout << attack.getname() << "对" << target.getname() << "使用了" << attack.skillName(skillindex) << endl;
		if (skillindex == 1) {//不同技能造成的效果不同
			target.changeatk(-target.getatk() / 8);
		}
		else if (skillindex == 2) {
			damage = (attack.getatk() - target.getdef()) * 1.5;
			return target.changehp(-damage);
		}
		else if (skillindex == 3) {
			int damage = (attack.getatk() - target.getdef()) * 2;
			return target.changehp(-damage);
		}
		else {
			int damage = attack.getatk() - target.getdef();
			return target.changehp(-damage);
		}
	}
	

	
	return false;
}

template <>
Race<1>::Race() : Base(HP)
{
	name = "妙蛙花";
	expneed[0] = 5;
	for (int i = 1; i < 14; ++i)
	{
		expneed[i] = expneed[i - 1] + 5 * i;
	}
	skillName[0] = "撞击";
	skillName[1] = "叫声";
	skillName[2] = "飞叶快刀";
	skillName[3] = "藤鞭";
	skillDscp[0] = "基础攻击";
	skillDscp[1] = "降低攻击";
	skillDscp[2] = "飞出叶片斩击对手";
	skillDscp[3] = "用藤蔓击打对手";
	pp[0] = 10;
	pp[1] = 5;
	pp[2] = 7;
}
template <>
bool Race<1>::attack(Pokemon &attack, Pokemon &target, int skillindex) const {//高生命型种族的攻击函数
	if (dodge(attack.getspe(), target.getspe())) {
		output += attack.getname() + "的攻击被躲掉了\n";
		return false;
	}
	bool crits = boot(attack.getspe(), target.getspe());
	int damage;
	if (crits) {
		output += "\n" + attack.getname() + "对" + target.getname() + "使用了" + attack.skillName(skillindex) + ",造成了暴击！！！\n";
		//cout << attack.getname() << "对" << target.getname() << "使用了" << attack.skillName(skillindex) << endl;
		if (skillindex == 1) {
			target.changeatk(-target.getatk() / 8);
		}
		else if (skillindex == 2) {
			damage = (attack.getatk() - target.getdef()) * 4;
			return target.changehp(-damage);
		}
		else if (skillindex == 3) {
			damage = (attack.getatk() - target.getdef()) * 3;
			return target.changehp(-damage);
		}
		else {
			damage = (attack.getatk() - target.getdef())*2;
			return target.changehp(-damage);
		}
	}
	else {
		output += "\n" + attack.getname() + "对" + target.getname() + "使用了" + attack.skillName(skillindex) + "\n";
		//cout << attack.getname() << "对" << target.getname() << "使用了" << attack.skillName(skillindex) << endl;
		if (skillindex == 1) {
			target.changeatk(-target.getatk() / 8);
		}
		else if (skillindex == 2) {
			damage = (attack.getatk() - target.getdef()) * 2;
			return target.changehp(-damage);
		}
		else if (skillindex == 3) {
			damage = (attack.getatk() - target.getdef()) * 1.5;
			return target.changehp(-damage);
		}
		else {
			damage = attack.getatk() - target.getdef();
			return target.changehp(-damage);
		}
	}
	
	return false;
}

template <>
Race<2>::Race() : Base(DEF)
{
	name = "杰尼龟";
	expneed[0] = 5;
	for (int i = 1; i < 14; ++i)
	{
		expneed[i] = expneed[i - 1] + 5 * i;
	}
	skillName[0] = "头槌";
	skillName[1] = "摇尾巴";
	skillName[2] = "水之波动";
	skillName[3] = "咬住";
	skillDscp[0] = "基础攻击";
	skillDscp[1] = "降低防御";
	skillDscp[2] = "用水的波动攻击对手";
	skillDscp[3] = "用尖锐的牙咬住对手";
	pp[0] = 10;
	pp[1] = 5;
	pp[2] = 5;
}

template <>
bool Race<2>::attack(Pokemon &attack, Pokemon &target, int skillindex) const {
	if (dodge(attack.getspe(), target.getspe())) {
		output += attack.getname() + "的攻击被躲掉了\n";
		return false;
	}
	bool crits = boot(attack.getspe(), target.getspe());
	int damage;
	if (crits) {
		output += "\n" + attack.getname() + "对" + target.getname() + "使用了" + attack.skillName(skillindex) + "造成了暴击!!!\n";

		//cout << attack.getname() << "对" << target.getname() << "使用了" << attack.skillName(skillindex) << endl;
		if (skillindex == 1) {
			target.changedef(-target.getdef() / 4);
		}
		else if (skillindex == 2) {
			int damage = (attack.getatk() - target.getdef()) * 4;
			return target.changehp(-damage);
		}
		else if (skillindex == 3) {
			int damage = (attack.getatk() - target.getdef()) * 3;
			return target.changehp(-damage);
		}
		else {
			int damage = (attack.getatk() - target.getdef()) * 2;
			return target.changehp(-damage);
		}
	}
	else {
		output += "\n" + attack.getname() + "对" + target.getname() + "使用了" + attack.skillName(skillindex) + "\n";

		//cout << attack.getname() << "对" << target.getname() << "使用了" << attack.skillName(skillindex) << endl;
		if (skillindex == 1) {
			target.changedef(-target.getdef() / 8);
		}
		else if (skillindex == 2) {
			int damage = (attack.getatk() - target.getdef()) * 2;
			return target.changehp(-damage);
		}
		else if (skillindex == 3) {
			int damage = (attack.getatk() - target.getdef()) * 1.5;
			return target.changehp(-damage);
		}
		else {
			int damage = attack.getatk() - target.getdef();
			return target.changehp(-damage);
		}
	}
	return false;
}

template <>
Race<3>::Race() : Base(SPE)
{
	name = "皮卡丘";
	expneed[0] = 5;
	for (int i = 1; i < 14; ++i)
	{
		expneed[i] = expneed[i - 1] + 5 * i;
	}
	skillName[0] = "电击";
	skillName[1] = "诡计";
	skillName[2] = "十万伏特";
	skillName[3] = "放电";
	skillDscp[0] = "基础攻击";
	skillDscp[1] = "提升攻击";
	skillDscp[2] = "向对手发出强烈电击";
	skillDscp[3] = "用耀眼的电击攻击自己周围所有的宝可梦";
	pp[0] = 10;
	pp[1] = 5;
	pp[2] = 5;
}
template <>
bool Race<3>::attack(Pokemon &attack, Pokemon &target, int skillindex) const {
	if (dodge(attack.getspe(), target.getspe())) {
		output += attack.getname() + "的攻击被躲掉了\n";
		return false;
	}
	bool crits = boot(attack.getspe(), target.getspe());
	int damage;
	if (crits) {
		output += "\n" + attack.getname() + "对" + target.getname() + "使用了" + attack.skillName(skillindex) + "造成了暴击！！！\n";

		//cout << attack.getname() << "对" << target.getname() << "使用了" << attack.skillName(skillindex) << endl;
		if (skillindex == 1) {
			attack.changeatk(attack.getatk() / 8);
		}
		else if (skillindex == 2) {
			int damage = (attack.getatk() - target.getdef()) * 4;
			return target.changehp(-damage);
		}
		else if (skillindex == 3) {
			int damage = (attack.getatk() - target.getdef()) * 3;
			return target.changehp(-damage);
		}
		else {
			int damage = (attack.getatk() - target.getdef())*2;
			return target.changehp(-damage);
		}
	}
	else {
		output += "\n" + attack.getname() + "对" + target.getname() + "使用了" + attack.skillName(skillindex) + "\n";

		//cout << attack.getname() << "对" << target.getname() << "使用了" << attack.skillName(skillindex) << endl;
		if (skillindex == 1) {
			attack.changeatk(attack.getatk() / 8);
		}
		else if (skillindex == 2) {
			int damage = (attack.getatk() - target.getdef()) * 2;
			return target.changehp(-damage);
		}
		else if (skillindex == 3) {
			int damage = (attack.getatk() - target.getdef()) * 1.5;
			return target.changehp(-damage);
		}
		else {
			int damage = attack.getatk() - target.getdef();
			return target.changehp(-damage);
		}
	}
	
	return false;
}


Pokemon::Pokemon(Base &pokrace, const string &pokname) :race(pokrace) {
	if (pokname.length() == 0)//如果没有起名字就用种族的名字代替
		name = race.raceName();
	else
		name = pokname;

	//初始化
	baseatk = race.getAtk();
	basedef = race.getDef();
	basespe = race.getSpeed();
	basehp = race.getHp();
	level = 1;
	exp = 0;
	for (int i = 0; i < 3; i++) {
		pp[i] = race.getpp(i);
	}

	cout << "获得了宝可梦" << name << endl;//打印初始化信息
	cout << "种族" << race.raceName() << " " << getracetype() << endl;
	cout << "力量" << baseatk << endl;
	cout << "防御" << basedef << endl;
	cout << "生命" << basehp << endl;
	cout << "敏捷" << basespe << endl;
	cout << "技能是" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "技能名称:" << race.getskillName(i) << endl;
		cout << "技能介绍:" << race.getskillDscp(i) << endl;
		if (i == 0)
			cout << "PP值无限" << endl;
		else
			cout << "PP:" << race.getpp(i - 1) << endl;
	}
	cout << endl;
}
string Pokemon::getracetype() const {//返回种族类型
	if (race.gettype() == ATK)
		return "高力量型";
	else if (race.gettype() == DEF)
		return "高防御型";
	else if (race.gettype() == HP)
		return "高生命型";
	else
		return "高敏捷型";
}
void Pokemon::changeatk(int n) {
	atk += n;
	if (atk < 1)
		atk = 1;
	if (n > 0)
		output += name + "的攻击+" + to_string(n) + "\n";
		//cout << name << "的攻击+" << n << endl;
	else
		output += name + "的攻击" + to_string(n) + "\n";
		//cout << name << "的攻击" << n << endl;
	output += name + "现在的攻击力是" + to_string(atk) + "\n";
	
}

void Pokemon::changedef(int n) {
	def += n;
	if (def < 1)
		def = 1;
	if (n >= 0)
		output += name + "的防御力+" + to_string(n) + "\n";
		//cout << name << "的防御力+" << n << endl;
	else
		output += name + "的防御力" + to_string(n) + "\n";
		//cout << name << "的防御力" << n << endl;
	output += name + "现在的防御力是" + to_string(def) + "\n";
	//cout << name << "现在的防御力是" << def << endl;
	
}

bool Pokemon::changehp(int n) {//改变生命值，如果生命值为0返回true	
	hp += n;
	if (hp < 0)
		hp = 0;
	output += name + "承受了" + to_string(n) + "的伤害\n";
	//cout << name << "承受了" << n << "的伤害" << endl;
	if (hp == 0) {
		output += name + "倒下了\n";
		//cout << name << "倒下了" << endl;
		
		return true;
	}
	else {
		output += name + "现在的生命值是" + to_string(hp) + "\n";
		//cout << name << "现在的生命值是" << hp << endl;
		return false;
	}
	
}

void Pokemon::changespe(int n) {	
	spe += n;
	if (spe < 1)
		spe = 1;
	if (n > 0)
		output += name + "的敏捷+" + to_string(n) + "\n";
		//cout << name << "的敏捷+" << n << endl;
	else
		output += name + "的敏捷" + to_string(n) + "\n";
		//cout << name << "的敏捷" << n << endl;
	output += name + "现在的敏捷是" + to_string(spe) + "\n";
	//cout << name << "现在的敏捷是" << spe << endl;
}

bool Pokemon::attack(Pokemon &target) {
	int skillindex = 0;
	int random = rand() % 4;//先随机选择一个技能进行攻击
	if (random != 0) {
		if (pp[random - 1] != 0) {//如果这个技能的pp值不为0，就使用该技能，反之使用0号技能
			skillindex = random;
			pp[random - 1]--;
		}
	}
	return race.attack(*this, target, skillindex);//攻击
}

bool Pokemon::gainexp(int n) {
	string infor;
	const char* information;
	char sen[MAX];

	if (level == 15)//如果满级，返回
		return false;
	
	exp += n;
	bool up = false;//用来侦测是否升级
	infor += name + "获得了" + to_string(n) + "点经验,"+to_string(exp)+"/"+to_string(race.getexpneed(level + 1))+"\n";
	while (exp >= race.getexpneed(level + 1) && level != 15) {//升级操作
		exp -= race.getexpneed(level + 1);//减去升级所要的经验
		up = true;
		level++;
		int gatk, gdef, ghp, gspe;
		gatk = 5;
		gdef = 2;
		ghp = 10;
		gspe = 5;
		Poktype A = race.gettype();
		if (A == ATK)//不同种类升级所加属性不同
			gatk += 4;
		else if (A == DEF)
			gdef += 2;
		else if (A == HP)
			ghp += 6;
		else
			gspe += 2;
		baseatk += gatk;
		basedef += gdef;
		basespe += gspe;
		basehp += ghp;
		infor += name + "升级了,现在" + to_string(level) + "级\n";
		infor += "ATK" + to_string(baseatk - gatk) + "-->" + to_string(baseatk) + "\n";
		infor += "DEF" + to_string(basedef - gdef) + "-->" + to_string(basedef) + "\n";
		infor += "SPE" + to_string(basespe - gspe) + "-->" + to_string(basespe) + "\n";
		infor += "HP" + to_string(basehp - ghp) + "-->" + to_string(basehp) + "\n";		
	}
	information = &infor[0];
	sprintf_s(sen, information);
	send(connSocket, sen, strlen(sen) + 1, 0);
	if (up == true)//升级了返回true
		return true;
	else
		return false;
}

bool Pokemon::gainexpfs(int n) {
	if (level == 15)//如果满级，返回
		return false;
	exp += n;
	bool up = false;//用来侦测是否升级
	while (exp >= race.getexpneed(level + 1) && level != 15) {//升级操作
		exp -= race.getexpneed(level + 1);//减去升级所要的经验
		up = true;
		level++;
		int gatk, gdef, ghp, gspe;
		gatk = 5;
		gdef = 2;
		ghp = 10;
		gspe = 5;
		Poktype A = race.gettype();
		if (A == ATK)//不同种类升级所加属性不同
			gatk += 4;
		else if (A == DEF)
			gdef += 2;
		else if (A == HP)
			ghp += 6;
		else
			gspe += 2;
		baseatk += gatk;
		basedef += gdef;
		basespe += gspe;
		basehp += ghp;
	}
	if (up == true)//升级了返回true
		return true;
	else
		return false;
}
void Pokemon::recover() {//宝可梦恢复函数
	atk = baseatk;
	def = basedef;
	spe = basespe;
	hp = basehp;
	for (int i = 0; i < 3; i++) {
		pp[i] = race.getpp(i);
	}
}

bool Battle::start() {
	timerA = 0;
	timerB = 0;
	pokA.recover();
	pokB.recover();
	while (1) {
		while (timerA < pokA.getspe() && timerB < pokB.getspe()) {//都还没到攻击时刻
			timerA++;
			timerB++;
		}
		if (timerA >= pokA.getspe() && timerB >= pokB.getspe()) {//两者同时攻击
			if (pokA.getspe() >= pokB.getspe()) {//如果A的敏捷高，则A先攻击
				if (pokA.attack(pokB))
					break;
				if (pokB.attack(pokA))
					break;
			}
			else {
				if (pokB.attack(pokA))
					break;
				if (pokA.attack(pokB))
					break;
			}
		}
		else if (timerA >= pokA.getspe()) {//实现高敏捷多攻击
			if (pokB.attack(pokA))
				break;
			timerA = 0;
		}
		else {
			if (pokA.attack(pokB))
				break;
			timerB = 0;
		}
	}
	memset(sendBuf, 0, MAX);
	if (pokA.gethp() == 0) {
		output += pokB.getname() + "赢了\n";
		//cout << pokB.getname() << "赢了" << endl;
		const char* out = &output[0];		
		sprintf_s(sendBuf, out);
		send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
		return 0;
	}
	else {
		output += pokA.getname() + "赢了\n";
		const char* out = &output[0];
		sprintf_s(sendBuf, out);
		send(connSocket, sendBuf, strlen(sendBuf) + 1, 0);
		//cout << pokA.getname() << "赢了" << endl;
		return 1;
	}
	output.clear();
}
