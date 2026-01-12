#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int run(istream &cin, ostream &cout) {
	int n, m;
	cin >> n >> m;

	int N = n + 1;

	typedef pair<ll, int> pa;
	vector<vector<pa>> conn(N);
	for (int i = 0; i < m; i++) {
		int from, to;
		ll len;
		cin >> from >> to >> len;
		conn[from].push_back({len, to});
	}

	const ll MAX = 1e18;
	vector<ll> dist(N, MAX);
	priority_queue<pa, vector<pa>, greater<pa>> q;
	q.push({0, 1});

	while(!q.empty()) {
		auto [len, to] = q.top();
		q.pop();
		if (dist[to] <= len) continue;

		dist[to] = len;
		for (auto [len1, to1] : conn[to]) {
			ll nl = len1 + len;
			if (nl > dist[to1]) continue;
			/*dist[to1] = nl;*/
			q.push({nl, to1});
		}
	}

	for (int i = 1; i < N; i++) {
		if (i > 1) cout << " ";
		cout << dist[i];
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
