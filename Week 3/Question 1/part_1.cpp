#include <iostream>
using namespace std;

class A {
public:
    int val;
	A() {
		val = 0;
	}
	A& GetObj() {
		return *this;
	}
	A(int n) {
		val = n;
	}
};

int main()  {
	A a;
    cout << a.val << endl;
    a.GetObj() = 5;
	cout << a.val << endl;
	return 0;
}