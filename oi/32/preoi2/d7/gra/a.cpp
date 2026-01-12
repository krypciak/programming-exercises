#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
	int n, k;
	cin >> n >> k;

	typedef pair<int, int> pt;
	vector<vector<pt>> OS(n, vector<pt>(k));
	for (int i = 0; i < n; i++) for (int j = 0; j < k; j++) {
		int val; cin >> val;
		OS[i][j].first = val;
	}
	for (int i = 0; i < n; i++) for (int j = 0; j < k; j++) {
		int val; cin >> val;
		OS[i][j].second = val;
	}

	vector<int> reqMet(n, k);
	vector<priority_queue<pt, vector<pt>, greater<pt>>> reqs(k);
	for (int i = 0; i < n; i++) for (int j = 0; j < k; j++) reqs[j].emplace(OS[i][j].first, i);

	vector<ll> CS(k, 0);
	bool lastWon = true;
	int sum = 0;
	while(lastWon) {
		lastWon = false;
		for (int j = 0; j < k; j++) {
			while (reqs[j].size()) {
				auto [sn, i] = reqs[j].top();
				if (CS[j] < sn) break;
				reqs[j].pop();
				if (--reqMet[i] == 0) {
					lastWon = true;
					for (int l = 0; l < k; l++) CS[l] += OS[i][l].second;
					sum++;
				}
			}
		}
	}
	cout << sum << '\n';
	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
	test("ex1");
	test("ex0");
	test("ex2");
	test("ex3");
	return 0;
}
#endif
