#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int a;
	cin >> a;
	cout << hex << a << endl;
	cout << dec << setfill('0') << setw(10) << a << endl;
	return 0;
}