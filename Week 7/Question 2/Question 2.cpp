#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	double a;
	cin >> a;
	cout << setprecision(5) << showpoint << fixed << a << endl;
	cout << scientific << setprecision(7) << a << endl;
	return 0;
}