#include <iostream>
#include <set>
#include <cmath>

using namespace std;

bool is_prime(int);
int get_prime_count(int);

class op {
public:
	bool operator() (int x, int y) {
		int count_a = 0, count_b = 0;
		count_a = get_prime_count(x);
		count_b = get_prime_count(y);
		if (count_a == count_b) {
			if (x < y) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (count_a > count_b) {
				return false;
			}
			else {
				return true;
			}
		}
	}
};

bool is_prime(int n) {
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) return false;
	}
	return true;
}

int get_prime_count(int n) {
	int sum = 0, tmp = 0;
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			tmp = n / i;
			if (is_prime(i)) sum++;
			if (is_prime(tmp) && i != tmp) sum++;
		}
	}
	return sum;
}

set<int, op> s;


int main() {
	int num, tmp, max, min;
	cin >> num;
	while (num--) {
		for (int i = 0; i < 10; i++) {
			cin >> tmp;
			s.insert(tmp);
		}
		max = *(s.rbegin());
		min = *(s.begin());
		s.erase(max);
		s.erase(min);
		cout << max << ' ' << min << endl;
	}
	return 0;
}