#include <iostream>
#include <map>
using namespace std;


class A {
public:
	static int count;
	A() { count++; }
	A(int a) { count++; }
	virtual ~A() {
		cout << "A::destructor" << endl;
	}
	void operator delete(void *a) {
		count--;
	}
};
class B :public A {
public:
	B() :A() {}
	B(int b) :A() {}
	B &operator=(B &b) {
		return b;
	}
	virtual ~B() {
		cout << "B::destructor" << endl;
	}
};


int A::count = 0;
void func(B b) { }
int main()
{
	A a1(5), a2;
	cout << A::count << endl;
	B b1(4);
	cout << A::count << endl;
	func(b1);
	cout << A::count << endl;
	A * pa = new B(4);
	cout << A::count << endl;
	delete pa;
	cout << A::count << endl;
	return 0;
}