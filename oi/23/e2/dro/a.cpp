#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> G;
vector<vector<int>> RG;
vector<bool> visited;

vector<int> postOrder;
void dfsPostOrder(int v) {
	visited[v] = true;
	for (int u : G[v]) if (!visited[u]) dfsPostOrder(u);
	postOrder.push_back(v);
}

int sId;
vector<int> GSId;
vector<vector<int>> sss;
void dfsCS(int v, int sId) {
	visited[v] = true;
	GSId[v] = sId;
	sss[sId].push_back(v);
	for (int u : RG[v]) if (!visited[u] and GSId[u] == -1) dfsCS(u, sId);
}

vector<vector<int>> SG;
vector<vector<int>> SRG;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n >> m;
	G = vector<vector<int>>(n+1);
	RG = vector<vector<int>>(n+1);
	for (int i = 0; i < m; i++) {
		int f, t;
		cin >> f >> t;
		G[f].push_back(t);
		RG[t].push_back(f);
	}

	visited = vector<bool>(n+1, false);
	postOrder = vector<int>();
	postOrder.reserve(n);
	for (int v = 1; v <= n; v++) if (!visited[v]) dfsPostOrder(v);
	reverse(postOrder.begin(), postOrder.end());

	sss = vector<vector<int>>();
	visited = vector<bool>(n+1, false);
	GSId = vector<int>(n+1, -1);
	sId = 0;
	for (int v : postOrder) if(!visited[v]) {
		sss.push_back({});
		dfsCS(v, sId);
		sId++;
	}

	int sssc = sss.size();
	SG = vector<vector<int>>(sssc);
	SRG = vector<vector<int>>(sssc);
	for (int v = 1; v <= n; v++) {
		for (int u : G[v]) {
			int vsid = GSId[v];
			int usid = GSId[u];
			if (vsid != usid) {
				SG[vsid].push_back(usid);
				SRG[usid].push_back(vsid);
			}
		}
	}

	visited = vector<bool>(sssc, false);

	queue<int> zeros;
	vector<int> degs(sssc);
	for (int v = 0; v < sssc; v++) {
		degs[v] = SRG[v].size();
		if (degs[v] == 0) zeros.push(v);
	}

	vector<int> topSort;
	topSort.reserve(sssc);
	while(zeros.size()) {
		int v = zeros.front();
		zeros.pop();
		topSort.push_back(v);
		for (int u : SG[v]) if (--degs[u] == 0) zeros.push(u);
	}


	vector<bool> bad(sssc, false);
	{
		vector<bool> canReach(sssc, false);
		int counter = 0;
		for (int v = sssc-1; v >= 0; v--, counter++) {
			for (int u : SG[v]) if (!canReach[u]) {
				canReach[u] = true;
				counter--;
			}
			if (counter != 0) bad[v] = true;
		}
	}
	{
		vector<bool> canReach(sssc, false);
		int counter = 0;
		for (int v = 0; v < sssc; v++, counter++) {
			for (int u : SRG[v]) if (!canReach[u]) {
				canReach[u] = true;
				counter--;
			}
			if (counter != 0) bad[v] = true;
		}
	}


	vector<int> out;
	for (int v = 0; v < sssc; v++) {
		if (bad[v]) continue;
		for (auto u : sss[v]) out.push_back(u);
	}
	cout << out.size() << '\n';
	sort(out.begin(), out.end());
	for (auto v : out) cout << v << ' ';

	return 0;
}


#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
	test("ex0");
	// test("ex1");
	return 0;
}
#endif
