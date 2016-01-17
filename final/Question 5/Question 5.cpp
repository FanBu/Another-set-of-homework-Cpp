#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class CMy_add {
public:
	int &my_sum;
	CMy_add(int &n) : my_sum(n) {};
	void operator() (int & v) {
		my_sum += (v % 8);
	}

};


int main(int argc, char* argv[]) {
	int v, my_sum = 0;
	vector<int> vec;
	cin >> v;
	while (v) {
		vec.push_back(v);
		cin >> v;
	}
	for_each(vec.begin(), vec.end(), CMy_add(my_sum));
	cout << my_sum << endl;
	return 0;
}