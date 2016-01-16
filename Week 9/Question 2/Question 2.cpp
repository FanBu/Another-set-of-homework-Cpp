#include <iostream>
#include <string>
using namespace std;

template <class T> 
class CMyistream_iterator{
private:
	istream & is;
	T elem;
public:
	CMyistream_iterator(istream & _cin) : is(_cin) {
		is >> elem;
	}
	T operator * (){
		return elem;
	}
	CMyistream_iterator & operator ++ (int k) {
		is >> elem;
		return *this;
	}
};


int main (){

	CMyistream_iterator<int> inputInt(cin);
	int n1, n2, n3;
	n1 = *inputInt;
	int tmp = *inputInt;
	cout << tmp << endl;
	inputInt++;
	n2 = *inputInt;
	inputInt++;
	n3 = *inputInt;
	cout << n1 << "," << n2 << "," << n3 << endl;
	CMyistream_iterator<string> inputStr(cin);
	string s1, s2;
	s1 = *inputStr;
	inputStr++;
	s2 = *inputStr;
	cout << s1 << "," << s2 << endl;
	return 0;
}