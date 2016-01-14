#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class student {
private:
	char name[20];
	int age;
	char id[20];
	int grade[4];

public:
	char* getName() {
		return name;
	};
	
	int getAge() {
		return age;
	}

	char* getId() {
		return id;
	}
	int getAverageGrade() {
		return (grade[0] + grade[1] + grade[2] + grade[3]) / 4;
	}

	void setName(char *temp) {
		strcpy(name, temp);
	}

	void setgrade0(int n) {
		grade[0] = n;
	}

	void setgrade1(int n) {
		grade[1] = n;
	}

	void setgrade2(int n) {
		grade[2] = n;
	}

	void setgrade3(int n) {
		grade[3] = n;
	}

	void setId(char *temp) {
		strcpy(id, temp);
	}

	void setAge(int n) {
		age = n;
	}
};

int main() {
	student stuA;
	char name[20], id[20];
	char age[4], grade[4][4];
	scanf("%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s", name, age, id, grade, grade + 1, grade + 2, grade + 3);
	stuA.setName(name);
	stuA.setId(id);
	stuA.setAge(atoi(age));
	stuA.setgrade0(atoi(grade[0]));
	stuA.setgrade1(atoi(grade[1]));
	stuA.setgrade2(atoi(grade[2]));
	stuA.setgrade3(atoi(grade[3]));

	cout << stuA.getName() << ',' << stuA.getAge() << ',' << stuA.getId() << ',' << stuA.getAverageGrade() << endl;

	return 0;
}