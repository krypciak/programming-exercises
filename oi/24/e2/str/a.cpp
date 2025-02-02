#include <bits/stdc++.h>
using namespace std;

class SEG {
	int n;
	vector<int> t;
	public:
	SEG(int n) : n(n) { t.assign(n*2, 0); }
	
	// [l, r)
	void add(int l, int r, int value) {
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) t[l++] += value;
			if (r&1) t[--r] += value;
		}
	}
	int query(int p) {
		int res = 0;
		for (p += n; p > 0; p >>= 1) res += t[p];
		return res;
	}
};

int n, m;
vector<vector<int>> G;


#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);
	vector<bool> O;
	vector<int> topSortT;

	cin >> n;
	G.assign(n+1, {});
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	vector<int> toVisit{1};
	int nnid = 1;
	vector<int> CT; // conversion table
	CT.assign(n+1, 0);
	CT[1] = nnid++;
	vector<int> P; // parents
	P.assign(n+1, 0);
	vector<pair<int, int>> CH; // child ranges [u, v)
	CH.assign(n+1, {0, 0});
	while(toVisit.size()) {
		vector<int> nextToVisit;
		nextToVisit.reserve(toVisit.size()*2);
		for (int v : toVisit) {
			int minC = nnid;
			for (int u : G[v]) {
				if (CT[u] != 0) continue;
				CT[u] = nnid++;
				P[u] = CT[v];
				nextToVisit.push_back(u);
			}
			int maxC = nnid;
			CH[v] = {minC, maxC};
		}
		toVisit = nextToVisit;
	}

	O.assign(n+1, false);
	cin >> m;
	int sep = 1;
	SEG S(n+1);
	while(m--) {
		int v;
		cin >> v;
		bool isPos = v > 0;
		v = abs(v);
		int uact = S.query(CT[v]);

		int val = (int)G[v].size() - 1 - uact;

		if (isPos) sep += val;
		else sep -= val;

		O[v] = isPos;
		int add = isPos ? 1 : -1;
		S.add(P[v], P[v]+1, add); // parent
		S.add(CH[v].first, CH[v].second, add); // children

		cout << sep << '\n';
	}
	return 0;
}
#ifdef TEST
int brute(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
	int n, m;
	vector<vector<int>> G;
	vector<bool> O;

	cin >> n;
	G.assign(n+1, {});
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	O.assign(n+1, false);
	cin >> m;
	int sep = 1;
	while(m--) {
		int v;
		cin >> v;
		int uact = 0;
		for (int u : G[abs(v)]) if (O[u]) uact++;

		int val = (int)G[v].size() - 1 - uact;
		if (v > 0) {
			sep += val;
			O[v] = true;
		} else {
			sep -= val;
			O[-v] = false;
		}
		cout << sep << '\n';
	}
	return 0;
}
string rtrim(string s) {
	auto end = s.find_last_not_of(" \r\t\n\v\f");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string outS, string expS) {
	if (outS == expS) 
	printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
	else
	printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: \n'%s'\n-----got: \n'%s'\n\n", name.c_str(), expS.c_str(), outS.c_str());
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
void testBrute() {
}
int main() {
	test("ex2");
	test("ex0");
	test("ex1");
	testBrute();
	return 0;
}
#endif
