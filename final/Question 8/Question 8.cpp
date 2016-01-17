#include <iostream>
#include <bitset>
#include <iomanip>

using namespace std;

int main() {
	int t, i, j, n_;
	unsigned long r;
	cin >> t;
	while (t--) {
		bitset<32> n;
		bitset<32> k;
		cin >> n_ >> i >> j;
		for (int m = 0; m < 32; m++) {
			n.set(m, (n_ % 2 == 1));
			n_ /= 2;
		}
		k.set(i, n[i]);
		k.set(j, ~n[j]);
		for (int m = i + 1; m < j; m++) {
			k.set(m, true);
		}
		r = k.to_ulong();
		cout << hex << r << endl;
	}
	return 0;
}