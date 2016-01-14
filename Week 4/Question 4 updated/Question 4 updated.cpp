#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const static int MAXSIZE = 202;

class BigInt
{
public:
	BigInt(const char* str);

public:
	BigInt operator+ (const BigInt& bi);
	BigInt operator- (const BigInt& bi);
	BigInt operator* (const BigInt& bi);
	BigInt operator/ (const BigInt& bi);
	BigInt& operator= (const BigInt& bi);
	bool operator< (const BigInt& bi);
	bool operator> (const BigInt& bi);
	bool operator== (const BigInt& bi);
	bool operator!= (const BigInt& bi);
	friend ostream& operator<< (ostream& o, const BigInt& bi);
	friend istream& operator>> (istream& i, BigInt& bi);

private:
	char str[MAXSIZE];
	int val[MAXSIZE];
	bool neg;
	int size;

private:
	void intToChar(BigInt& bi);
};

BigInt::BigInt(const char* str = "") {
	memset(this->str, 0, MAXSIZE*sizeof(char));
	memset(val, 0, MAXSIZE*sizeof(int));
	neg = false;
	size = strlen(str);
	if (str != "") {
		memcpy(this->str, str, this->size);
		for (int i = 0; i < size; i++) {
			this->val[i] = (int)this->str[size - i - 1] - '0';
		}
	}
}

void BigInt::intToChar(BigInt& temp) {
	while (temp.size > 0 && temp.val[temp.size - 1] == 0) {
		temp.size -= 1;
	}
	for (int i = 0; i < temp.size; i++) {
		temp.str[i] = (char)(temp.val[temp.size - 1 - i] + '0');
	}
}

BigInt BigInt::operator+ (const BigInt &bi) {
	BigInt temp;
	if (!strcmp(this->str, "0") && !strcmp(bi.str, "0")) {
		return "0";
	}
	temp.size = (size > bi.size ? size : bi.size) + 1;
	for (int i = 0; i < temp.size; i++) {
		temp.val[i] += val[i] + bi.val[i];
		if (i + 1 != MAXSIZE) {
			temp.val[i + 1] += temp.val[i] / 10;
		}
		temp.val[i] = temp.val[i] % 10;
	}
	intToChar(temp);
	return temp;
}

BigInt BigInt::operator- (const BigInt &bi) {
	BigInt temp;
	int flag = 0;
	if (size > bi.size) {
		flag = 1;
	}
	else if (size < bi.size) {
		flag = -1;
	}
	else {
		flag = strcmp(this->str, bi.str);
	}
	if (!flag) {
		return "0";
	}
	if (flag > 0) {
		temp.size = size;
		for (int i = 0; i < temp.size; i++) {
			temp.val[i] += val[i] - bi.val[i];
			if (temp.val[i] < 0) {
				if (i + 1 != MAXSIZE) {
					temp.val[i + 1] -= 1;
				}
				temp.val[i] += 10;
			}
		}
	}
	else {
		temp.neg = true;
		temp.size = bi.size;
		for (int i = 0; i < bi.size; i++) {
			temp.val[i] += bi.val[i] - this->val[i];
			if (temp.val[i] < 0) {
				temp.val[i + 1] -= 1;
				temp.val[i] += 10;
			}
		}
	}
	intToChar(temp);
	return temp;
}

BigInt BigInt::operator* (const BigInt &bi) {
	BigInt temp;
	if (!strcmp(this->str, "0") || !strcmp(bi.str, "0")) {
		return "0";
	}
	temp.size = size + bi.size + 1;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < bi.size; j++) {
			temp.val[i + j] += val[i] * bi.val[j];
			if (i + j + 1 != MAXSIZE) {
				temp.val[i + j + 1] += temp.val[i + j] / 10;
			}
			temp.val[i + j] = temp.val[i + j] % 10;
		}
	}
	intToChar(temp);
	return temp;
}

BigInt BigInt::operator/ (const BigInt& bi) {
	BigInt temp;
	if (!strcmp(str, "0")) {
		return "0";
	}
	if (!strcmp(bi.str, "1")) {
		return *this;
	}
	temp.size = size;
	int flag = 0;
	if (size > bi.size) {
		flag = 1;
	}
	else if (size < bi.size) {
		flag = -1;
	}
	else {
		flag = strcmp(str, bi.str);
	}
	if (flag < 0) {
		return "0";
	}
	if (flag == 0) {
		return "1";
	}
	else {
		BigInt qt;
		BigInt div = *this;
		BigInt dir = bi;
		BigInt tmp;
		while (div.size >= dir.size) {
			tmp = "1";
			if (div.str[0] >= dir.str[0] && strcmp(div.str, dir.str) > 0) {
				int k = div.size - dir.size;
				for (int i = 0; i < k; i++) {
					tmp = tmp * "10";
				}
				div = div - dir * tmp;
				qt = qt + tmp;
			}
			else if (div.str[0] >= dir.str[0] && div.size - dir.size >= 1) {
				int k = div.size - dir.size - 1;
				for (int i = 0; i < k; i++) {
					tmp = tmp * "10";
				}
				div = div - dir * tmp;
				qt = qt + tmp;
			}
			else if ((div.str[0] < dir.str[0] && div.size == dir.size) || (div.size == dir.size && strcmp(div.str, dir.str) < 0)) {
				return qt;
			}
			else if (div.str[0] < dir.str[0] && div.size - dir.size >= 1) {
				int k = div.size - dir.size - 1;
				for (int i = 0; i < k; i++) {
					tmp = tmp * "10";
				}
				div = div - dir*tmp;
				qt = qt + tmp;
			}
			else {
				//div = div - dir;
				//qt = qt + "1";
			}
		}
		return qt;
	}
	if (!strcmp(temp.str, "0")) {
		return "0";
	}
	intToChar(temp);
	return temp;
}

BigInt& BigInt::operator= (const BigInt& bi) {
	if (this == &bi) {
		return *this;
	}
	memset(this->str, 0, MAXSIZE * sizeof(char));
	memset(this->val, 0, MAXSIZE * sizeof(int));
	size = bi.size;
	neg = bi.neg;
	memcpy(str, bi.str, bi.size);
	for (int i = 0; i < size; i++) {
		val[i] = bi.val[i];
	}
	return *this;
}

bool BigInt::operator== (const BigInt& bi) {
	if (this == &bi) {
		return true;
	}
	if (size < bi.size || size > bi.size) {
		return false;
	}
	else {
		return strcmp(str, bi.str) == 0;
	}
}

bool BigInt::operator!= (const BigInt &bi) {
	return !(*this == bi);
}

bool BigInt::operator< (const BigInt &bi) {
	if (size > bi.size) {
		return false;
	}
	if (size < bi.size) {
		return true;
	}
	return strcmp(str, bi.str) < 0;
}

bool BigInt::operator> (const BigInt &bi) {
	if (*this < bi || *this == bi) {
		return false;
	}
	return true;
}

ostream& operator<< (ostream& o, const BigInt& bi) {
	if (bi.neg) {
		o << '-';
	}
	for (int i = 0; i < bi.size; i++) {
		o << bi.str[i];
	}
	return o;
}

istream& operator>> (istream& i, BigInt& bi) {
	string temp;
	i >> temp;
	bi = temp.c_str();
	return i;
}

int main() {
	BigInt a, b;
	string opr;
	cin >> a >> opr >> b;
	int i;
	if (opr == "+") {
		cout << a + b << endl;
	}
	else if (opr == "-") {
		cout << a - b << endl;
	}
	else if (opr == "*") {
		cout << a * b << endl;
	}
	else {
		cout << a / b << endl;
	}
	return 0;
}