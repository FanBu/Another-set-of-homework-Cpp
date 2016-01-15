#include <iostream>
using namespace std;

template <class T1> 
class CArray3D{
public:
	template <class T2>
	class CArray2D {
	public:
		template <class T3>
		class CArray1D {
		public:
			T3 * p;
			CArray1D() {
				p = NULL;
			}
			void init(int _a) {
				p = new T3[_a];
			}
			T3 & operator [](int _a) {
				return p[_a];
			}
		};
		CArray1D<T1> * p1;
		CArray2D() {
			p1 = NULL;
		}
		void init(int _b, int _a) {
			p1 = new CArray1D<T2>[_b];
			for (int i = 0; i < _b; i++) {
				p1[i].init(_a);
			}
		}
		CArray1D<T2> & operator[](int _b) {
			return p1[_b];
		}
	};
	CArray2D<T1> *p2;
	CArray3D() {
		p2 = NULL;
	}
	void init(int _c, int _b, int _a) {
		p2 = new CArray2D<T1>[_c];
		for (int i = 0; i < _c; i++) {
			p2[i].init(_b, _a);
		}
	}
	CArray2D<T1> & operator[](int _c) {
		return p2[_c];
	}
	CArray3D(int a, int b, int c) {
		init(a, b, c);
	}
};

int main()
{
	CArray3D<int> a(3, 4, 5);
	int No = 0;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 5; ++k)
				a[i][j][k] = No++;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 5; ++k)
				cout << a[i][j][k] << ",";
	return 0;
}