#include <iostream>
using namespace std;


class CType {
public:
	int num;
	int operator ++(int k) {
		int m = num;
		num = num * num;
		return m;
	}
	void setvalue(int n) {
		num = n;
	}
};

ostream & operator << (ostream & o, CType & c) {
	o << c.num;
	return o;
}


int main(int argc, char* argv[]) {
	CType obj;
	int n;
	cin >> n;
	while (n) {
		obj.setvalue(n);
		cout << obj++ << " " << obj << endl;
		cin >> n;
	}
	return 0;
}