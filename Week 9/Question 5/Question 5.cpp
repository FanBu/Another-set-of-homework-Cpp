#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <cstdio>

using namespace std;

multimap <int, int> s;

int main() {
	int n, id, power, lower_power = 0, higher_power;
	s.insert(make_pair(1000000000, 1));
	scanf("%d", &n);
	while (n--) {
		scanf("%d %d", &id, &power);
		multimap<int, int>::iterator p;
		p = s.insert(make_pair(power, id));
		if (p == s.begin()) {
			++p;
			printf("%d %d\n", id, p->second);
		}
		else if (p == s.end()) {
			printf("%d %d\n", id, p->second);
		}
		else {
			--p;
			lower_power = p->first;
			++p; ++p;
			higher_power = p->first;
			if ((higher_power - power) < (power - lower_power)) {
				printf("%d %d\n", id, p->second);
			}
			else {
				--p; --p;
				printf("%d %d\n", id, p->second);
			}
		}
		
	}
	return 0;
}