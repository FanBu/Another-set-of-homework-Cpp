#include <iostream>
#include <list>
#include <map>
#include <string>
#include <stdlib.h>

using namespace std;

map<int, list<int> > *seq;
string tmp;

void new_id(int n){
	list<int> new_list;
	(*seq).insert(pair<int, list<int> >(n, new_list));
}

void add_id_num(int n, int m) {
	(*seq)[n].push_back(m);
}

void merge_id1_id2(int a, int b) {
	(*seq)[a].merge((*seq)[b]);
}

void unique_id(int n) {
	(*seq)[n].sort();
	(*seq)[n].unique();
}

void out_id(int n) {
	int tmp = (*seq)[n].size();
	(*seq)[n].sort();
	if (tmp > 0) {
		list<int>::const_iterator i;
		for (i = (*seq)[n].begin(); i != (*seq)[n].end(); i++) {
			cout << *i << ' ';
		}
	}
	cout << endl;
}

int main() {
	int n, m;
	seq = new map<int, list<int> >;
	(cin >> n).get();
	for (int i = 0; i < n; i++) {
		getline(cin, tmp);
		const char* chars = tmp.c_str();
		switch (tmp[0]) {
		case 'n':
			new_id(atoi(chars + 4));
			break;
		case 'a':
			m = tmp.rfind(' ');
			add_id_num(atoi(chars + 4), atoi(chars + m));
			break;
		case 'o':
			out_id(atoi(chars + 4));
			break;
		case 'u':
			unique_id(atoi(chars + 7));
			break;
		case 'm':
			m = tmp.rfind(' ');
			merge_id1_id2(atoi(chars + 6), atoi(chars + m));
			break;
		}
	}
	return 0;
}