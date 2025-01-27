#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	cin >> n;

	int N = n+2;
	vector<vector<pair<int, int>>> G(N);
	vector<vector<pair<int, int>>> RG(N);
	vector<int> W(N, 0);
	for (int u = 1; u <= n; u++) {
		int t, k;
		cin >> t >> k;
		W[u] = t;
		for (int j = 0; j < k; j++) {
			int v;
			cin >> v;

			G[v].push_back({u, t});
			RG[u].push_back({v, t});
		}
	}

	vector<int> degs(N);
	for (int v = 1; v <= n; v++) { 
		degs[v] = RG[v].size();
		if (degs[v] == 0) {
			degs[v]++;
			G[0].push_back({v, W[v]});
			RG[v].push_back({0, W[v]});
		}
	}
	const int META = n+1;
	for (int v = 1; v <= n; v++) {
		if (G[v].size() == 0) {
			degs[META]++;
			G[v].push_back({META, 0});
			RG[META].push_back({v, 0});
		}
	}
	queue<int> empty;
	empty.push(0);

	vector<int> topsort;
	topsort.reserve(n);
	while(empty.size()) {
		int v = empty.front();
		empty.pop();
		topsort.push_back(v);

		for (auto [u, _] : G[v]) if (--degs[u] == 0) empty.push(u);
	}
	if ((int)topsort.size() != N) { cout << "CYKL" << endl; return 0; }

	vector<int> maxDist(N, -1);
	maxDist[0] = 0;
	for (int v : topsort) 
		for (auto [u, len] : G[v]) 
			maxDist[u] = max(maxDist[u], maxDist[v] + len);

	int md = maxDist[META];
	cout << md << endl;

	vector<int> revMaxDist(N, -1);
	revMaxDist[META] = 0;
	reverse(topsort.begin(), topsort.end());
	for (int v : topsort)
		for (auto [u, len] : RG[v])
			revMaxDist[u] = max(revMaxDist[u], revMaxDist[v] + len);

	int q;
	cin >> q;
	while(q--) {
		int v, nw;
		cin >> v >> nw;
		int leeway = md - (maxDist[v] + revMaxDist[v]);
		if (nw > leeway) {
			cout << "TAK" << '\n';
		} else {
			cout << "NIE" << '\n';
		}
	}

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
