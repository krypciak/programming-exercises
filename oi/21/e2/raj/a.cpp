#include <bits/stdc++.h>
using namespace std;

class Seg {
	int n;
	vector<int> t;
public:
	Seg(int n) : n(n) {
		t = vector<int>(n*2, 0);
	}
	int query(int p) {
  		int res = 0;
  		for (p += n; p > 0; p >>= 1) res = max(res, t[p]);
  		return res;
	}
	void set(int l, int r, int value) {
  		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    		if (l&1) { t[l] = max(t[l], value); l++; }
    		if (r&1) { r--; t[r] = max(t[r], value); } 
  	}
}
};

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m;
	cin >> n >> m;
	vector<vector<int>> initG(n+1);
	vector<vector<int>> RG(n+1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		initG[a].push_back(b);
		RG[b].push_back(a);
	}

	vector<vector<int>> G(n+1);
	vector<int> topSort;
	{
		vector<int> degs(n+1);
		for (int v = 1; v <= n; v++) degs[v] = RG[v].size();

		topSort.reserve(n);
		queue<int> zeros;
		for (int v = 1; v <= n; v++) if (degs[v] == 0) zeros.push(v);

		while (zeros.size()) {
			int v = zeros.front();
			zeros.pop();
			topSort.push_back(v);
			for (int u : initG[v]) if (--degs[u] == 0) zeros.push(u);
		}

		RG.assign(n+1, {});
		vector<int> tab(n+1);

		for (int v = 1; v < n+1; v++) tab[topSort[v-1]] = v;
		for (int nv = 1; nv < n+1; nv++) {
			for (int u : initG[topSort[nv-1]]) {
				G[nv].push_back(tab[u]);
				RG[tab[u]].push_back(nv);
			}
		}
	}

	vector<int> dist(n+1, 0); // longestEnd
	for (int v = 0; v < n+1; v++) for (int u : G[v]) dist[u] = max(dist[u], dist[v] + 1);
	vector<int> prefix(n+2, 0); // longestBefore
	for (int v = 1; v < n+1; v++) prefix[v] = max(prefix[v-1], dist[v]);

	vector<int> Rdist(n+1, 0); // longestStart
	for (int v = n; v >= 0; v--) for (int u : RG[v]) Rdist[u] = max(Rdist[u], Rdist[v] + 1);
	vector<int> Rprefix(n+2, 0); // longestAfter
	for (int v = n; v >= 0; v--) Rprefix[v] = max(Rprefix[v+1], Rdist[v]);

	/*std::cout << "dist: " << dist[n+1] << ", " << Rdist[0] << endl;*/

	vector<int> bypass(n+1, 0);
	Seg SEG(n+1);

	for (int v = 1; v <= n; v++) {
		for (int u : G[v]) {
			if (u == v+1) continue;
			SEG.set(v+1, u, dist[v] + 1 + Rdist[u]);
		}
	}
	for (int v = 1; v <= n; v++) bypass[v] = SEG.query(v);

	vector<int> skipMaxDist(n+1, INT_MAX);
	for (int v = 1; v <= n; v++) skipMaxDist[v] = max({prefix[v-1], Rprefix[v+1], bypass[v]});

	auto minSkipIte = min_element(skipMaxDist.begin(), skipMaxDist.end());
	int minI = distance(skipMaxDist.begin(), minSkipIte);

	cout << topSort[minI-1] << ' ';
	cout << skipMaxDist[minI] << '\n';
	return 0;
}

#ifdef TEST
int brute(istream &cin, ostream &cout) {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> G(n+1);
	vector<vector<int>> RG(n+1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		RG[b].push_back(a);
	}
	vector<int> degs(n+1);
	for (int v = 1; v <= n; v++) degs[v] = RG[v].size();

	queue<int> zeros{};
	for (int v = 1; v <= n; v++) if (RG[v].size() == 0) zeros.push(v);

	vector<int> topSort;
	topSort.reserve(n);

	while (zeros.size()) {
		int v = zeros.front();
		zeros.pop();
		topSort.push_back(v);
		for (int u : G[v]) if (--degs[u] == 0) zeros.push(u);
	}

	int maxV = -1;
	int maxL = 0;
	for (int i = 1; i <= n; i++) {
		vector<int> dist(n+1, 0); // longestEnd
		for (int j = 1; j <= n; j++) {
			int v = topSort[j-1];
			if (v == i) continue;
			for (int u : G[v]) {
				if (u == i) continue;
				dist[u] = max(dist[u], dist[v] + 1);
			}
		}

		auto das = max_element(dist.begin(), dist.end());
		if (maxL < *das) {
			maxL = *das;
			maxV = i;
		}
	}
	cout << maxV << ' ' << maxL;
	return 0;
}
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
void testBrute() {
	random_device rd;
    	mt19937 g(rd());

	for (int i = 0; i < 10; i++) {
		int n = 10, m = 30;
		string inp = to_string(n) + " " + to_string(m) + "\n";
		set<int> seen;
		vector<int> tab(n);
		for (int i = 0; i < n; i++) tab[i] = i+1;
		shuffle(tab.begin(), tab.end(), g);

		for (int j = 0; j < m; j++) {
			int v, u;
			do {
				v = rand()%n + 1; 
				u = rand()%(n-v+1) + v; 
			} while(v == u or seen.contains(v+u*n));
			seen.insert(v+u*n);

			v = tab[v-1];
			u = tab[u-1];
			inp += to_string(v) + " " + to_string(u) + "\n";
		}

		istringstream in(inp);
		ostringstream out;
		run(in, out);
		string outS = rtrim(out.str());
		stringstream S(outS);
		int U, L;
		S >> U >> L;

		istringstream in1(inp);
		ostringstream out1;
		brute(in1, out1);
		string expS = rtrim(out1.str());
		stringstream S1(outS);
		int U1, L1;
		S1 >> U1 >> L1;

		if (L != L1) {
			printT("brute " + to_string(i), outS, expS);
			break;
		} else {
			printT("brute " + to_string(i), "", ""); 
		}
	}
}
int main() {
	test("ex0");
	test("ex1");
	test("ex2");
	test("ex3");
	test("ex4");
	testBrute();
	return 0;
}
#endif
