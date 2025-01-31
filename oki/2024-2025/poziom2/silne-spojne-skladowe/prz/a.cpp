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

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
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
#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \n\r\t\f\v");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string outS, string expS) {
	if (outS == expS) {
		print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
	} else {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} fail! expected: \n'{}'\n---got: \n'{}'\n\n", name, expS, outS);
	}
}
void test(string name) {
	ifstream in(name+".in");
	ostringstream out;

	run(in, out);
	string outS = rtrim(out.str());

	ifstream exp(name+".out");
	string expS(istreambuf_iterator<char>{exp}, {});
	expS = rtrim(expS);

	printT(name, outS, expS);
}
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
