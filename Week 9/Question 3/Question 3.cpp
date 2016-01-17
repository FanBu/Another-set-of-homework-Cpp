#include <iostream>
#include <set>
#include <string>
#include <stdlib.h>

using namespace std;
multiset<int> s;
set<int> added;

void add_n(int n) {
	s.insert(n);
	added.insert(n);
	cout << s.count(n) << endl;
}

void del_n(int n) {
	cout << s.erase(n) << endl;
}

void ask_n(int n) {
	int m = 0;;
	m = s.count(n);
	if (added.count(n) > 0) {
		cout << "1 " << m << endl;
	}
	else {
		cout << "0 0" << endl;
	}
}

int main() {
	int n;
	(cin >> n).get();
	string tmp;
	while (n--) {
		getline(cin, tmp);
		const char * chars = tmp.c_str();
		switch (tmp[1]) {
		case 'd':
			add_n(atoi(chars + 4));
			break;
		case 's':
			ask_n(atoi(chars + 4));
			break;
		case 'e':
			del_n(atoi(chars + 4));
			break;
		}
	}
	return 0;
}