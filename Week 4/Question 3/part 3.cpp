#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
	int m, n;
	int* ptr = NULL;

public:
	Array2(int _m, int _n):m(_m), n(_n) {
		ptr = new int[m * n];
	}

	Array2() {
		ptr = NULL;
		m = 0; n = 0;
	}

	Array2(Array2 & array2) {
		m = array2.m;
		n = array2.n;
		ptr = new int[m * n];
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				*(ptr + i * n + j) = array2(i, j);
			}
		}
	}

	int * operator[](const int i) {
		return ptr + n * i;
	}
	int operator() (int i, int j) {
		return *(ptr + n * i + j);
	}
};


int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}