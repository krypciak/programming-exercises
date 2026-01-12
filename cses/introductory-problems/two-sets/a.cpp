#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;

	if (n % 4 == 1 or n % 4 == 2) {
		cout << "NO" << endl;
		return 0;
	}

	vector<int> set1;
	vector<int> set2;

	if (n % 4 == 3) {
		for (int i = 1; i < n / 4 + 1; i++) {
			set1.push_back(i);
			set1.push_back(n - i);
		}
		set1.push_back(n);

		for (int i = n / 4 + 1; i < n / 2 + 1; i++) {
			set2.push_back(i);
			set2.push_back(n - i);
		}
	} else if (n % 4 == 0) {
		for (int i = 1; i < n / 4 + 1; i++) {
			set1.push_back(i);
			set1.push_back(n - i + 1);
		}
		for (int i = n / 4 + 1; i < n / 2 + 1; i++) {
			set2.push_back(i);
			set2.push_back(n - i + 1);
		}

	}

	cout << "YES" << endl;
	cout << set1.size() << endl;
	for (int i = 0; i < (int)set1.size(); i++) {
		if (i > 0) cout << " ";
		cout << set1[i];
	}
	cout << endl;
	cout << set2.size() << endl;
	for (int i = 0; i < (int)set2.size(); i++) {
		if (i > 0) cout << " ";
		cout << set2[i];
	}
	cout << endl;

	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
	test("ex7");
	test("ex5");
	test("ex4");
	test("ex8");
	return 0;
}
#endif
