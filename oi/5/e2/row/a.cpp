#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<int> sizes;
vector<int> beg;

bool isConst(int u) { return u == 0 or u == 1; }

void inpEq(vector<int> &up, istream &cin) {
	up.reserve(n);
	int lup; cin >> lup;
	string upS; cin >> upS;
	for (char c : upS) {
		if (c == '0' or c == '1') up.push_back(c-'0');
		else for (int j = 0; j < sizes[c-'a']; j++) up.push_back(beg[c-'a']+j);
	}
}
vector<vector<int>> G;
void addEdge(int i, const vector<int> &from, const vector<int> &to) {
	int u = from[i];
	int v = to[i];
	G[u].push_back(v);
}

string pow2(int exponent) {
    string result = "1";
    for (int i = 0; i < exponent; i++) {
        int carry = 0;
        for (auto it = result.rbegin(); it != result.rend(); it++) {
            int digit = (*it - '0') * 2 + carry;
            *it = (digit % 10) + '0';
            carry = digit / 10;
        }
        if (carry) result.insert(result.begin(), carry + '0');
    }
    return result;
}

string calc(istream &cin) {
	cin >> n;

	beg.assign(n+1, 0);
	beg[0] = 2;
	sizes.assign(n, 0);
	for (int i = 0; i < n; i++) cin >> sizes[i];
	for (int i = 0; i < n; i++) beg[i+1] = beg[i] + sizes[i];
	vector<int> up; inpEq(up, cin);
	vector<int> down; inpEq(down, cin);
	if (up.size() != down.size()) return "0";
	int eqLen = up.size();

	for (int i = 0; i < eqLen; i++) if (isConst(down[i]) and isConst(up[i]) and (down[i] != up[i])) return "0";

	int MV = beg[n];
	G.assign(MV, {});
	for (int i = 0; i < eqLen; i++) { addEdge(i, down, up); addEdge(i, up, down); }

	ll forests = 0;
	vector<bool> visited(MV, false);
	vector<int> conValues(MV, -1);
	for (int v = 2; v < MV; v++) {
		if (visited[v]) continue;
		int con = -1;

		vector<int> tree;
		queue<int> Q;
		Q.push(v);
		visited[v] = true;
		while(Q.size()) {
			int u = Q.front();
			Q.pop();
			for (int w : G[u]) {
				if (isConst(w)) {
					if (con != -1 and con != w) return "0";
					con = w;
					continue;
				}
				if (visited[w]) continue;
				visited[w] = true;
				Q.push(w);
				tree.push_back(w);
			}
		}
		if (con != -1) for (int u : tree) conValues[u] = con;
		if (con == -1) forests++;
	}
	return pow2(forests);
}

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int r;
	cin >> r;
	while(r--) cout << calc(cin) << '\n';

	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	test("ex2");
	test("ex3");
	test("ex4");
	test("ex5");
	test("ex6");
	return 0;
}
#endif
