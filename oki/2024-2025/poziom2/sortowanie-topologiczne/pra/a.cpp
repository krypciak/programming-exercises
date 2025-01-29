#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);


	int n, m;
	cin >> n >> m;

	vector<int> D(n+1, 0);
	for (int v = 1; v <= n; v++) D[v] = v-1;

	vector<vector<bool>> T(n+1);
	for (int v = 1; v <= n; v++) {
		int size = n-v;
		T[v] = vector<bool>(size, true);
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		if (u >= v) continue;
		D[v]--;
		T[u][v-u-1] = false;
	}

	priority_queue<int> Q;
	for (int v = 1; v <= n; v++) if (D[v] == 0) Q.push(v);

	while (Q.size()) {
		int v = Q.top();
		Q.pop();
		cout << v << ' ';
		for (int u = v+1; u <= n; u++) if (T[v][u-v-1] and --D[u] == 0) Q.push(u);
	}
	return 0;
}

#ifdef TEST
int brut(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m;
	cin >> n >> m;
	vector<set<int>> deleted(n+1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		deleted[a].insert(b);
	}

	vector<vector<int>> G(n+1);
	vector<vector<int>> RG(n+1);
	for (int v = 1; v <= n; v++) {
		for (int u = 1; u < v; u++) {
			if (deleted[u].count(v) == 0) {
				G[u].push_back(v);
				RG[v].push_back(u);
			}
		}
	}
	priority_queue<int> Q;
	vector<int> D(n+1, 0);
	for (int v = 1; v <= n; v++) {
		D[v] = RG[v].size();
		if (D[v] == 0) Q.push(v);
	}
	while (Q.size()) {
		int v = Q.top();
		Q.pop();
		cout << v << ' ';
		for (int u : G[v]) if (--D[u] == 0) Q.push(u);
	}
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
void testBrut() {
	for (int i = 0; i < 10; i++) {
		int n = 10, m = 5;
		string inp = to_string(n) + " " + to_string(m) + '\n';
		set<int> was;
		for (int j = 0; j < m; j++) {
			int u = rand()%n + 1;
			int v = rand()%n + 1;
			if (u == v or was.contains(u+v*n)) { j--; continue; }
			was.insert(u+v*n);
			inp += to_string(u) + " " + to_string(v) + '\n';
		}
		/*cout << inp << endl;*/

		string solveS;
		{
		istringstream in(inp);
		ostringstream out;
		run(in, out);
		solveS = rtrim(out.str());
		}

		string brutS;
		{
		istringstream in(inp);
		ostringstream out;
		brut(in, out);
		brutS = rtrim(out.str());
		}
		printT("brute " + to_string(i), solveS, brutS);
		if (solveS != brutS) {
			break;
		}
	}
}
int main() {
	test("ex2");
	test("ex0");
	test("ex1");
	testBrut();
	return 0;
}
#endif
