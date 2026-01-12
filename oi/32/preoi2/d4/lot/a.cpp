#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
	typedef long long ll;
	int n, m;
	cin >> n >> m;

	vector<ll> W(n+1);
	for (int i = 1; i <= n; i++) cin >> W[i];

	vector<vector<int>> G(n+1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	struct De {
		int v /* wierzholek */;
		ll h /* height */, mh /* can rise */, d /* dystans */;
		bool operator<(const De &a) const {
			// if (d == a.d) return h < a.h;
			return d+h < a.d+a.h;
		}
		bool operator>(const De &a) const {
			// if (d == a.d) return h > a.h;
			return d+h > a.d+a.h;
		}
	};
	vector<De> dist(n+1, {-1, INT_MAX, 0, INT_MAX});
	dist[1] = {1, 0, 0, 0};
	priority_queue<De, vector<De>, greater<De>> Q;
	Q.push(dist[1]);

	while(Q.size()) {
		De s = Q.top();
		Q.pop();

		if (dist[s.v] < s and dist[s.v].d != s.d) continue; 
		auto [v, h, mh, d] = s;
		// std::cout << "v: " << v << ", h: " << h << ", mh: " << mh << ", d: " << d << endl;

		if (v == n) goto brkMeta;

		mh++;
		for (int u : G[v]) {
			const ll uh = W[u];
			ll umh = mh;
			ll ud = d+1;
			ll nuh = h;

			if (uh == h) {
			} else if (uh < h) {
				umh++;
				nuh--;
			} else {
				ll das = uh - (h + mh);
				if (das >= 0) {
					ud += das;
					umh = 0;
				} else {
					umh = -das;
				}
				nuh = uh;
			}

			De ns = {u, nuh, umh, ud};
			if (u == n) { // META
				ns.d += ns.h;
				if (ns < dist[u]) {
					dist[u] = ns;
					Q.push(ns);
				}
			} else {
				if (ns < dist[u]) {
					Q.push(ns);
					dist[u] = ns;
				}
			}
		}
	}
brkMeta:
	cout << dist[n].d << endl;
	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	test("ex2");
	return 0;
}
#endif
