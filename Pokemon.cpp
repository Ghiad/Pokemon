#include"Pokemon.h"

Base::Base(Poktype typ) {
	type = typ;

	Atk = 10;
	Def = 5;
	Hp = 25;
	Speed = 10;

	switch (typ) //��ͬ���忪ʼ�����Բ�ͬ
	{
	case ATK:
		Atk += 3;
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
Race<0>::Race() : Base(ATK)//ATK����ĳ�ʼ��
{
	name = "С����";
	expneed[0] = 5;
	for (int i = 1; i < 14; ++i)//��ʼ����������
	{
		expneed[i] = expneed[i - 1] + 5 * i;
	}
	skillName[0] = "ץ";
	skillName[1] = "����";
	skillName[2] = "��Ϣ";
	skillName[3] = "�������";
	skillDscp[0] = "��������";
	skillDscp[1] = "���͹�����";
	skillDscp[2] = "��ǿ�ҵ���Ϣ�������";
	skillDscp[3] = "����ַ�������";
	pp[0] = 10;
	pp[1] = 5;
	pp[2] = 5;
}
template <>
bool Race<0>::attack(Pokemon &attack, Pokemon &target, int skillindex) const {//������������Ĺ�������
	cout << attack.getname() << "��" << target.getname() << "ʹ����" << attack.skillName(skillindex) << endl;
	if (skillindex == 1) {//��ͬ������ɵ�Ч����ͬ
		target.changeatk(-target.getatk() / 8);
	}
	else if (skillindex == 2) {
		int damage = (attack.getatk() - target.getdef()) * 1.5;
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
	return false;
}

template <>
Race<1>::Race() : Base(HP)
{
	name = "���ܻ�";
	expneed[0] = 5;
	for (int i = 1; i < 14; ++i)
	{
		expneed[i] = expneed[i - 1] + 5 * i;
	}
	skillName[0] = "ײ��";
	skillName[1] = "����";
	skillName[2] = "��Ҷ�쵶";
	skillName[3] = "�ٱ�";
	skillDscp[0] = "��������";
	skillDscp[1] = "���͹���";
	skillDscp[2] = "�ɳ�ҶƬն������";
	skillDscp[3] = "�������������";
	pp[0] = 10;
	pp[1] = 5;
	pp[2] = 7;
}
template <>
bool Race<1>::attack(Pokemon &attack, Pokemon &target, int skillindex) const {//������������Ĺ�������
	cout << attack.getname() << "��" << target.getname() << "ʹ����" << attack.skillName(skillindex) << endl;
	if (skillindex == 1) {
		target.changeatk(-target.getatk() / 8);
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
	return false;
}

template <>
Race<2>::Race() : Base(DEF)
{
	name = "�����";
	expneed[0] = 5;
	for (int i = 1; i < 14; ++i)
	{
		expneed[i] = expneed[i - 1] + 5 * i;
	}
	skillName[0] = "ͷ�";
	skillName[1] = "ҡβ��";
	skillName[2] = "ˮ֮����";
	skillName[3] = "ҧס";
	skillDscp[0] = "��������";
	skillDscp[1] = "���ͷ���";
	skillDscp[2] = "��ˮ�Ĳ�����������";
	skillDscp[3] = "�ü������ҧס����";
	pp[0] = 10;
	pp[1] = 5;
	pp[2] = 5;
}

template <>
bool Race<2>::attack(Pokemon &attack, Pokemon &target, int skillindex) const {
	cout << attack.getname() << "��" << target.getname() << "ʹ����" << attack.skillName(skillindex) << endl;
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
	return false;
}

template <>
Race<3>::Race() : Base(SPE)
{
	name = "Ƥ����";
	expneed[0] = 5;
	for (int i = 1; i < 14; ++i)
	{
		expneed[i] = expneed[i - 1] + 5 * i;
	}
	skillName[0] = "���";
	skillName[1] = "���";
	skillName[2] = "ʮ�����";
	skillName[3] = "�ŵ�";
	skillDscp[0] = "��������";
	skillDscp[1] = "��������";
	skillDscp[2] = "����ַ���ǿ�ҵ��";
	skillDscp[3] = "��ҫ�۵ĵ�������Լ���Χ���еı�����";
	pp[0] = 10;
	pp[1] = 5;
	pp[2] = 5;
}
template <>
bool Race<3>::attack(Pokemon &attack, Pokemon &target, int skillindex) const {
	cout << attack.getname() << "��" << target.getname() << "ʹ����" << attack.skillName(skillindex) << endl;
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
	return false;
}


Pokemon::Pokemon(const Base &pokrace, const string &pokname) :race(pokrace) {
	if (pokname.length() == 0)//���û�������־�����������ִ���
		name = race.raceName();
	else
		name = pokname;

	//��ʼ��
	baseatk = race.getAtk();
	basedef = race.getDef();
	basespe = race.getSpeed();
	basehp = race.getHp();
	level = 1;
	exp = 0;
	for (int i = 0; i < 3; i++) {
		pp[i] = race.getpp(i);
	}

	cout << "����˱�����" << name << endl;//��ӡ��ʼ����Ϣ
	cout << "����" << race.raceName() << " " << getracetype() << endl;
	cout << "����" << baseatk << endl;
	cout << "����" << basedef << endl;
	cout << "����" << basehp << endl;
	cout << "����" << basespe << endl;
	cout << "������" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "��������:" << race.getskillName(i) << endl;
		cout << "���ܽ���:" << race.getskillDscp(i) << endl;
		if (i == 0)
			cout << "PPֵ����" << endl;
		else
			cout << "PP:" << race.getpp(i - 1) << endl;
	}
	cout << endl;
}
string Pokemon::getracetype() const {//������������
	if (race.gettype() == ATK)
		return "��������";
	else if (race.gettype() == DEF)
		return "�߷�����";
	else if (race.gettype() == HP)
		return "��������";
	else
		return "��������";
}
void Pokemon::changeatk(int n) {
	atk += n;
	if (atk < 1)
		atk = 1;
	if (n > 0)
		cout << name << "�Ĺ���+" << n << endl;
	else
		cout << name << "�Ĺ���" << n << endl;
	cout << name << "���ڵĹ�������" << atk << endl;
}

void Pokemon::changedef(int n) {
	def += n;
	if (def < 1)
		def = 1;
	if (n > 0)
		cout << name << "�ķ�����+" << n << endl;
	else
		cout << name << "�ķ�����" << n << endl;
	cout << name << "���ڵķ�������" << def << endl;
}

bool Pokemon::changehp(int n) {//�ı�����ֵ���������ֵΪ0����true
	hp += n;
	if (hp < 0)
		hp = 0;
	cout << name << "������" << n << "���˺�" << endl;
	if (hp == 0) {
		cout << name << "������" << endl;
		return true;
	}
	else {
		cout << name << "���ڵ�����ֵ��" << hp << endl;
		return false;
	}
}

void Pokemon::changespe(int n) {
	spe += n;
	if (spe < 1)
		spe = 1;
	if (n > 0)
		cout << name << "������+" << n << endl;
	else
		cout << name << "������" << n << endl;
	cout << name << "���ڵ�������" << spe << endl;
}

bool Pokemon::attack(Pokemon &target) {
	int skillindex = 0;
	int random = rand() % 4;//�����ѡ��һ�����ܽ��й���
	if (random != 0) {
		if (pp[random - 1] != 0) {//���������ܵ�ppֵ��Ϊ0����ʹ�øü��ܣ���֮ʹ��0�ż���
			skillindex = random;
			pp[random - 1]--;
		}
	}
	return race.attack(*this, target, skillindex);//����
}

bool Pokemon::gainexp(int n) {
	if (level == 15)//�������������
		return false;
	
	exp += n;
	bool up = false;//��������Ƿ�����
	cout << name << "�����" << n << "�㾭��" << endl;
	while (exp >= race.getexpneed(level + 1)) {//��������
		exp -= race.getexpneed(level + 1);//��ȥ������Ҫ�ľ���
		up = true;
		level++;
		int gatk, gdef, ghp, gspe;
		gatk = 5;
		gdef = 2;
		ghp = 10;
		gspe = 5;
		Poktype A = race.gettype();
		if (A == ATK)//��ͬ���������������Բ�ͬ
			gatk += 4;
		else if (A == DEF)
			gdef += 3;
		else if (A == HP)
			ghp += 6;
		else
			gspe += 3;
		baseatk += gatk;
		basedef += gdef;
		basespe += gspe;
		basehp += hp;
		cout << name << "������," << "����" << level << "��" << endl;
		cout << "ATK " << baseatk - gatk << "-->" << baseatk << endl;
		cout << "DEF " << basedef - gdef << "-->" << basedef << endl;
		cout << "SPE " << basespe - gspe << "-->" << basespe << endl;
		cout << "HP " << basehp - ghp << "-->" << basehp << endl;

	}
	if (up == true)//�����˷���true
		return true;
	else
		return false;
}

void Pokemon::recover() {//�����λָ�����
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
		while (timerA < pokA.getspe() && timerB < pokB.getspe()) {//����û������ʱ��
			timerA++;
			timerB++;
		}
		if (timerA >= pokA.getspe() && timerB >= pokB.getspe()) {//����ͬʱ����
			if (pokA.getspe() >= pokB.getspe()) {//���A�����ݸߣ���A�ȹ���
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
		else if (timerA >= pokA.getspe()) {//ʵ�ָ����ݶ๥��
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
	if (pokA.gethp() == 0) {
		//cout << pokB.getname() << "Ӯ��" << endl;
		return 0;
	}
	else {
		//cout << pokA.getname() << "Ӯ��" << endl;
		return 1;
	}
}