#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;


class MyString {
public:
	string s;
	bool operator < (MyString & a) {
		return (s < a.s);
	}
	bool operator == (MyString & a) {
		return (s == a.s);
	}
	bool operator > (MyString & a) {
		return (s > a.s);
	}
	MyString(const char * c) {
		s = c;
	}
	MyString() {
		s = "";
	}
	MyString & operator + (MyString & a) {
		MyString * c = new MyString;
		c->s = s + a.s;
		return *c;
	}
	MyString & operator += (MyString & a) {
		s += a.s;
		return *this;
	}
	char & operator[] (int n) {
		return s[n];
	}
	string & operator() (int a, int b) {
		string * c = new string;
		*c = s.substr(a, b);
		return *c;
	}
};

ostream & operator << (ostream & o, MyString & m) {
	o << m.s;
	return o;
}
MyString & operator + (MyString & m, char * c) {
	MyString * a = new MyString;
	MyString * b = new MyString;
	*a = c;
	b->s = m.s + a->s;
	return *b;
}
MyString & operator += (MyString & m, char * c) {
	m = m + c;
	return m;
}
MyString & operator + (char * c, MyString & m) {
	MyString * a = new MyString;
	MyString * b = new MyString;
	*a = c;
	b->s = a->s + m.s;
	return *b;
}



int CompareString(const void * e1, const void * e2)
{
	MyString * s1 = (MyString *)e1;
	MyString * s2 = (MyString *)e2;
	if (*s1 < *s2)
		return -1;
	else if (*s1 == *s2)
		return 0;
	else if (*s1 > *s2)
		return 1;
}
int main()
{
	MyString s1("abcd-"), s2, s3("efgh-"), s4(s1);
	MyString SArray[4] = { "big","me","about","take" };
	cout << "1. " << s1 << s2 << s3 << s4 << endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A';
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray, 4, sizeof(MyString), CompareString);
	for (int i = 0; i < 4; i++)
		cout << SArray[i] << endl;
	cout << s1(0, 4) << endl;
	cout << s1(5, 10) << endl;
	return 0;
}