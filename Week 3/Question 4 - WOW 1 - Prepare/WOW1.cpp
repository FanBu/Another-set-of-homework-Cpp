#include <iostream>
#include <iomanip>
using namespace std;

enum typeT { dragon, ninja, iceman, lion, wolf };
enum legionT { red, blue };
char typeName[6][7] = { "dragon", "ninja", "iceman", "lion", "wolf", "error" };
char legionName[3][6] = { "red", "blue", "error" };

char *tName(typeT type) {
	switch (type) {
	case 0: return typeName[0];
	case 1: return typeName[1];
	case 2: return typeName[2];
	case 3: return typeName[3];
	case 4: return typeName[4];
	};
	return typeName[6];
}

char *lName(legionT type) {
	switch (type) {
	case 0: return legionName[0];
	case 1: return legionName[1];
	default: return legionName[2];
	}
}

class Warrior {
	typeT type;
	legionT legion;
	int id;
	int hp;

public:
	Warrior(int id_, typeT type_, legionT legion_, int hp_):
		id(id_), type(type_), legion(legion_), hp(hp_) {}
};

class City {
	legionT legion;
	int hpCurr;
	int count;
	int typeCount[5];
	int tCurr;

private:
	void printOnSpawn(int time, typeT type) {
		cout << time << ' ' << type << endl;
	}

	string typeName(typeT type) {
		switch (type) {
		case 0: return "dragon";
		case 1: return "ninja";
		case 2: return "iceman";
		case 3: return "lion";
		case 4: return "wolf";
		}
	}

public:
	static int hpMax;
	static int hpList[5];
	const static typeT spawnSequence[2][5];

	City(legionT legion_) :
		legion(legion_), count(0), hpCurr(hpMax), tCurr(0) 
	{
		for (int i = 0; i < 5; i++) {
			typeCount[i] = 0;
		}
	};

	bool spawn(int time) {
		for (int i = 0; i < 5; i++, ++tCurr, tCurr %= 5) {
			typeT typeCurr = spawnSequence[legion][tCurr];
			if (hpCurr - hpList[typeCurr] >= 0) {
				count++;
				typeCount[typeCurr]++;
				hpCurr -= hpList[typeCurr];
				cout << setfill('0') << setw(3) << time << ' ';
				cout << lName(legion) << ' ';
				cout << tName(typeCurr) << ' ';
				cout << count << ' ';
				cout << "born with strength " << hpList[typeCurr] << ',';
				cout << typeCount[typeCurr] << ' ';
				cout << tName(typeCurr) << " in ";
				cout << lName(legion) << " headquarter" << endl;
				++tCurr;
				tCurr %= 5;
				return true;
			}
		}
		cout << setfill('0') << setw(3) << time << ' ';
		cout << lName(legion) << ' ';
		cout << "headquarter stops making warriors" << endl;
		return false;
	}
};

int City::hpMax = 0;
int City::hpList[5] = { 0 };
const typeT City::spawnSequence[2][5] = { {iceman, lion, wolf, ninja, dragon}, {lion, dragon, ninja, iceman, wolf} };

void spawn(City hqRed, City hqBlue) {
	int time = 0;
	bool flag1 = true;
	bool flag2 = true;
	while (flag1 && flag2) {
		flag1 = hqRed.spawn(time);
		flag2 = hqBlue.spawn(time);
		time++;
	}
	while (flag1) {
		flag1 = hqRed.spawn(time);
		time++;
	}
	while (flag2) {
		flag2 = hqBlue.spawn(time);
		time++;
	}
	int i = 0;
}


int main() {
	int nCase;
	cin >> nCase;
	for (int i = 0; i < nCase; i++) {
		cin >> City::hpMax;
		for (int j = 0; j < 5; j++) {
			cin >> City::hpList[j];
		}
		City hqRed = City(red);
		City hqBlue = City(blue);
		cout << "Case:" << i + 1 << endl;
		spawn(hqRed, hqBlue);
	}
	return 0;
}