#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;
vector<vector<int>> G;
vector<vector<int>> RG;
vector<bool> visited;
vector<int> post;

void dfsPost(int v) {
	visited[v] = true;
	for (int u : G[v]) if (!visited[u]) dfsPost(u);
	post.push_back(v);
}


int sId;
vector<vector<int>> sss;
vector<int> GSId;
void dfsS(int v, int sId) {
	GSId[v] = sId;
	sss[sId].push_back(v);
	for (int u : RG[v]) if (GSId[u] == -1) dfsS(u, sId);
}

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n;
	vector<ll> costs(n);
	for (int i = 0; i < n; i++) cin >> costs[i];

	cin >> m;

	G = vector<vector<int>>(n+1);
	RG = vector<vector<int>>(n+1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		RG[b].push_back(a);
	}

	visited = vector<bool>(n+1, false);
	post = vector<int>();
	post.reserve(n);
	for (int v = 1; v <= n; v++) if (!visited[v]) dfsPost(v);
	reverse(post.begin(), post.end());

	sId = 0;
	sss = vector<vector<int>>();
	GSId = vector<int>(n+1, -1);
	for (int v : post) if (GSId[v] == -1) {
		sss.push_back({});
		dfsS(v, sId);
		sId++;
	}
	
	ll sum = 0;
	ll poss = 1;
	for (auto members : sss) {
		 ll costMin = LONG_MAX;
		 int costMinC = 0;
		 for (auto v : members) {
			 ll cost = costs[v-1];
			 if (cost == costMin) costMinC++;
			 else if (cost < costMin) {
				 costMin = cost;
				 costMinC = 1;
			 }
		 }
		 assert(costMinC != 0);
		 sum += costMin;
		 poss *= costMinC;
	}

	cout << sum << ' ' << poss;

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
