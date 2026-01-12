#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
#define endl "\n";

	int n, q;
	cin >> n >> q;

	vector<int> G(n+1);
	for (int i = 1; i <= n; i++) {
		cin >> G[i];
	}

	const int MAXLG = 30;
	vector<vector<int>> skok(MAXLG+1, vector<int>(n+1));

	for (int i = 1; i <= n; i++) skok[0][i] = G[i];
	for (int i = 1; i <= MAXLG; i++) for (int j = 1; j <= n; j++) skok[i][j] = skok[i-1][skok[i-1][j]];

	while (q--) {
		int v, x;
		cin >> v >> x;

		int dist = 1 << MAXLG;
		for (int i = MAXLG; i >= 0; i--) {
			if (x >= dist) {
				v = skok[i][v];
				x -= dist;
			}
			dist /= 2;
		}
		cout << v << endl;
	}

	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif

