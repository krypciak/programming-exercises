#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
	int n;
	cin >> n;

	typedef unsigned long long ll;

	const ll moves = (1 << n) - 1;
	cout << moves << endl;

	const int BOTTOM = 1e6;
	vector<stack<int>> t(3);
	for (int i = 0; i < 3; i++) t[i].push(BOTTOM);
	for (int i = n; i >= 1; i--) t[0].push(i);

	typedef pair<int, int> pt;
	for (unsigned int i = 0; i < moves; i++) {
		if (i % 2 == 0) {
			auto [sm, smI] = min({(pt){t[0].top(), 0}, {t[1].top(), 1}, {t[2].top(), 2}});
			t[smI].pop();

			int dir = (n % 2 == 0) ? 1 : -1;
			int ni = smI + dir;
			if (ni < 0) ni = 2;
			ni %= 3;

			if (t[ni].top() <= sm) ni += dir;
			if (ni < 0) ni = 2;
			ni %= 3;

			t[ni].push(sm);
			cout << smI+1 << " " << ni+1 << endl;
		} else {
			auto [sm, smI] = min({(pt){t[0].top(), 0}, {t[1].top(), 1}, {t[2].top(), 2}});
			if (smI == 0) {
				tie(sm, smI) = min((pt){t[1].top(), 1}, {t[2].top(), 2});
			} else if (smI == 1) {
				tie(sm, smI) = min((pt){t[0].top(), 0}, {t[2].top(), 2});
			} else if (smI == 2) {
				tie(sm, smI) = min((pt){t[0].top(), 0}, {t[1].top(), 1});
			} 
			t[smI].pop();

			int dir = (n % 2 == 0) ? -1 : 1;
			int ni = smI+dir;
			if (ni < 0) ni = 2;
			ni %= 3;

			if (t[ni].top() <= sm) ni += dir;
			if (ni < 0) ni = 2;
			ni %= 3;

			t[ni].push(sm);
			cout << smI+1 << " " << ni+1 << endl;
		}
	}

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
