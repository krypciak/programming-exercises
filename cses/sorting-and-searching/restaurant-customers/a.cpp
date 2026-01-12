#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
	
	int n;
	cin >> n;
	vector<int> ent(n);
	vector<int> lea(n);
	for (int i = 0; i < n; i++) {
		cin >> ent[i] >> lea[i];
	}
	sort(ent.begin(), ent.end());
	sort(lea.begin(), lea.end());

	int i = 0, j = 0;
	int custMax = 0;
	int cust = 0;
	while (i < n) {
		if (ent[i] <= lea[j]) {
			i++;
			cust++;
			custMax = max(custMax, cust);
		} else {
			j++;
			cust--;
		}
	}
	cout << custMax << endl;
	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
