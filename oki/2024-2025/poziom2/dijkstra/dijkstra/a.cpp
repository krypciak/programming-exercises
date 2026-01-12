#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m;

struct GE {
	ll len;
	int to;
	int m;
	bool active;

	bool operator<(const GE &a) const { return len < a.len; }
};
vector<vector<GE*>> g;
vector<pair<int, int>> prevn;

ll dij(bool hasNeg) {
	typedef pair<ll, int> pl;
	priority_queue<pl, vector<pl>, greater<pl>> pq;
	pq.push({0, 1});
	vector<ll> dist(n+1, LLONG_MAX);
	dist[1] = 0;
	prevn = vector<pair<int, int>>(n+1);
	vector<bool> visited(n+1, false);

	while(pq.size()) {
		auto [l, v] = pq.top();
		pq.pop();
		if (!hasNeg) visited[v] = true;

		if (v == n) return l;

		if (dist[v] < l) continue;

		for (auto ref : g[v]) {
			auto [l1, v1, i1, active] = *ref;
			if (!hasNeg && visited[v1]) continue;
			if (!active) continue;

			ll nl = l + l1;
			if (nl < dist[v1]) {
				pq.push({nl, v1});
				dist[v1] = nl;
				prevn[v1] = {v, i1};
			}
		}
	}
	return dist[n];
}

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n >> m;
	if (n == 1) {
		cout << 0 << endl;
		return 0;
	}

	g = vector<vector<GE*>>(n+1);

	vector<GE> edges(m*2);
	for (int i = 0; i < m; i++) {
		int a, b;
		ll c;
		cin >> a >> b >> c;

		edges[i] = {c, b, i, true};
		g[a].push_back(&edges[i]);

		edges[i+m] = {-c, a, i+m, false};
		g[b].push_back(&edges[i+m]);
	}

	if (dij(false) == LLONG_MAX) { cout << -1 << endl; return 0; }

	vector<int> pOrig;
	{
		pOrig.reserve(n);
		int v = n;
		while(v != 1) {
			int i = prevn[v].second;
			pOrig.push_back(i);
			assert(i < m);

			edges[i].active = false;
			edges[i+m].active = true;
			
			v = prevn[v].first;
		}
		reverse(pOrig.begin(), pOrig.end());
	}

	if (dij(true) == LLONG_MAX) { cout << -1 << endl; return 0; }
	vector<int> pNew;
	{
		pNew.reserve(n);
		int v = n;
		while(v != 1) {
			int i = prevn[v].second;
			pNew.push_back(i);

			v = prevn[v].first;
		}
		reverse(pNew.begin(), pNew.end());
	}

	vector<int> inter(m, 0);
	for (auto v : pOrig) inter[v]++;
	for (auto v : pNew) { if (v >= m) v -= m; inter[v]++; }

	vector<pair<int, ll>> out1;
	out1.push_back({edges[pOrig[0]].to, edges[pOrig[0]].len});
	out1.push_back({edges[pNew[0]].to, edges[pNew[0]].len});

	ll sum = 0;
	for (auto [v, len] : out1) {
		while (v != n) {
			for (auto r : g[v]) {
				if (r->m >= m || inter[r->m] != 1) continue;
				v = r->to;
				len += r->len;
				break;
			}
		}
		sum += len;
	}

	cout << sum << endl;

	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
