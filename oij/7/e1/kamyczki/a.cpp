#include <bits/stdc++.h>

using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

#define endl "\n";
	int n, s;
	cin >> n >> s;
	
	vector<int> inp(n+1);
	for (int i = 1; i < n; i++) cin >> inp[i];
	inp[n] = 0;

	const int MAXLG = 30;
	const int CANTJUMP = 2000000;
	vector<vector<int>> skok(MAXLG+1, vector<int>(n+1, CANTJUMP));
	for (int i = 1; i <= n; i++) skok[0][i] = i;

	vector<int> psum(n+1);
	psum[0] = 0;
	for (int i = 1; i <= n; i++) psum[i] = psum[i-1] + inp[i];
	for (int j = 1; j <= n-1; j++) {
		auto ji = next(psum.begin(), j);
		int upperV = s + psum[j-1];
		auto upper = upper_bound(ji, next(ji, min(s, n-j+1)), upperV);
		int index = min(n, (int)distance(psum.begin(), upper));
		skok[1][j] = index;
		/*print("j: {}, upper: {}, index: {}\n", j, *upper, index);*/
	}

	for (int i = 2; i <= MAXLG; i++) {
		for (int j = 1; j <= n; j++) {
			if (skok[i-1][j] == CANTJUMP) break;
			skok[i][j] = skok[i-1][skok[i-1][j]];
		}
	}

	int p;
	cin >> p;

	while(p--) {
		int v, x;
		cin >> v >> x;
		if (x < v) swap(x, v);

		int jumps = 0;
		for (int i = MAXLG, jumpC = 1<<(MAXLG-1); i >= 1 && v < x;) {
			if (skok[i][v] <= x || i == 1) {
				v = skok[i][v];
				jumps += jumpC;
			} else {
				i--;
				jumpC/=2;
			}
		}
		cout << jumps << endl;
	}

	return 0;
}


#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	test("ex2");
	return 0;
}
#endif
