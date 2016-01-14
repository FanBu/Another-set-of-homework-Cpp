#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int min(int a, int b) {
	if (a < b) return a;
	return b;
}

int diff(int a, int b) {
	int temp = a - b;
	if (temp > 0) {
		return temp;
	}
	return -temp;
}


class Bignum {
public:
	char num[10002] = "";
	int len;

	Bignum(char* _num) {
		strcpy(num, _num);
		clear();
	}
	Bignum() {
		len = 0;
	}

	char& operator[] (int i) {
		return num[i];
	}
	void clear() {
		bool neg;
		char temp[10002];
		int i;
		neg = (num[10000] == '-');
		for (i = 0; i < 10002 && num[i]!= '\0' && num[i] == '0'; i++) {}
		if (num[i] == '\0') {
			num[0] = '0';
			num[1] = '\0';
		}
		else if (num[i] != '0') {
			strcpy(temp, &num[i]);
			strcpy(num, temp);
		}
		len = strlen(num);
		if (neg) num[10000] = '-';
	}
	Bignum operator+ (Bignum& num2) {
		Bignum temp;
		int c = 0, _max = max(len, num2.len), _min = min(len, num2.len);
		int _diff = diff(len, num2.len);
		int i;
		temp[_max+1] = '\0';
		if (len >= num2.len) {
			for (i = _max - 1; i >= _diff; i--) {
				int a = num[i] - '0';
				int b = num2.num[i - _diff] - '0';
				temp[i + 1] = (a + b + c) % 10 + '0';
				c = (a + b + c) / 10;
			}
			for (i = _diff - 1; i >= 0; i--) {
				temp[i + 1] = (num[i] - '0' + c) % 10 + '0';
				c = (num[i] - '0' + c) / 10;
			}
		}
		if (len < num2.len) {
			for (i = _max - 1; i >= _diff; i--) {
				int a = num[i - _diff] - '0';
				int b = num2.num[i] - '0';
				temp[i + 1] = (a + b + c) % 10 + '0';
				c = (a + b + c) / 10;
			}
			for (i = _diff - 1; i >= 0; i--) {
				temp[i + 1] = (num2.num[i] - '0' + c) % 10 + '0';
				c = (num2.num[i] - '0' + c) / 10;
			}
		}
		temp[0] = c + '0';
		temp.clear();
		return temp;
	}
	Bignum operator- (Bignum& num2) {
		Bignum temp;
		int c = 0, _max = max(len, num2.len), _min = min(len, num2.len);
		int _diff = diff(len, num2.len);
		int i;
		if (len > num2.len || len == num2.len && strcmp(num, num2.num) >= 0) {
			for (i = _max - 1; i >= _diff; i--) {
				int a = num[i] - '0';
				int b = num2.num[i - _diff] - '0';
				temp[i] = (a - b - c) % 10 + '0';
				if (a - b - c < 0) {
					c = 1;
					temp[i] += 10;
				}
				else c = 0;
			}
			for (i = _diff - 1; i >= 0; i--) {
				temp[i] = (num[i] - '0' - c) % 10 + '0';
				if (num[i] - '0' - c < 0) {
					temp[i] += 10;
					c = 1;
				}
				else c = 0;
			}
			temp.clear();
			return temp;
		}
		else {
			temp = num2 - *this;
			temp.num[10000] = '-';
			return temp;
		}
	}
	Bignum operator* (Bignum& num2) {
		Bignum *ptr1 = this, *ptr2 = &num2, temp, sum;
		int c = 0, _max = max(len, num2.len), _min = min(len, num2.len);
		int _diff = diff(len, num2.len);
		int i, j;
		if (len < num2.len) {
			ptr1 = &num2;
			ptr2 = this;
		}
		for (i = (*ptr2).len - 1; i >= 0; i--) {
			temp = (*ptr1).multInt((*ptr2)[i] - '0');
			for (j = 0; j < (*ptr2).len - 1 - i; j++) {
				temp = temp.multInt(10);
			}
			sum = sum + temp;
		}
		sum.clear();
		return sum;
	}
	Bignum multInt(int n) {
		Bignum temp;
		int i, c = 0;
		if (n < 0 || n > 10) {
			return *this;
		}
		if (n == 10) {
			temp = *this;
			temp[len] = '0';
			temp[len + 1] = '\0';
			temp.clear();
			return temp;
		}
		for (i = len - 1; i >= 0; i--) {
			temp.num[i + 1] = (c + n * (num[i] - '0')) % 10 + '0';
			c = (c + n * (num[i] - '0')) / 10;
		}
		temp[0] = c + '0';
		temp.clear();
		return temp;
	}
	Bignum operator/ (Bignum& num2) {
		Bignum temp, factor("1");
		int i = 1;
		char number[10002];
		while (1) {
			if ((*this - num2).num[10000] == '-') {
				factor = "0";
				factor.clear();
				return factor;
			}
			temp = num2 * factor;
			if ((*this - temp).num[10000] == '-') {
				i--;
				_itoa(i, number, 10);
				factor = number;
				factor.clear();
				return factor;
			}
			i++;
			_itoa(i, number, 10);
			factor = number;
			factor.clear();
		}
	}
};

ostream & operator<<(ostream &o, Bignum &n) {
	if (n.num[10000] == '-') {
		cout << '-';
	}
	o << n.num;
	return o;
}



int main() {
	Bignum a, b, c;
	char _a[10002], _b[10002], symbol;
	cin >> _a;
	cin >> symbol;
	cin >> _b;
	a = _a;
	b = _b;
	switch (symbol) {
	case '+': c = a + b; break;
	case '-': c = a - b; break;
	case '*': c = a * b; break;
	case '/': c = a / b; break;
	}
	cout << c << endl;
	return 0;
}