#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


vector<vector<int>> children;
vector<int> D;
int n, m;
int root;

bool check(int t) {
    vector<int> dyn(n+1, -1e9);
    vector<int> fire(n+1, 1e9);
    int used = 0;

    stack<pair<int, bool>> S;
    S.emplace(root, false);

    while (!S.empty()) {
        auto [u, visited] = S.top();
        S.pop();

        if (!visited) {
            S.emplace(u, true);
            for (auto it = children[u].rbegin(); it != children[u].rend(); ++it) {
                S.emplace(*it, false);
            }
        } else {
            dyn[u] = D[u] ? 0 : -1e9;
            fire[u] = 1e9;

            for (int v : children[u]) {
				dyn[u] = max(dyn[u], dyn[v] + 1);
				fire[u] = min(fire[u], fire[v] + 1);
            }

            if (dyn[u] != -1e9 && fire[u] != 1e9 && dyn[u] + fire[u] <= t) {
                dyn[u] = -1e9;
            }

            if (dyn[u] >= t || (u == root && dyn[u] != -1e9)) {
                used++;
                if (used > m) return false;
                dyn[u] = -1e9;
                fire[u] = 0;
            }
        }
    }

    return used <= m;
}


#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

    cin >> n >> m;

    D.assign(n+1, 0);
    for (int i = 1; i <= n; i++) cin >> D[i];

    vector<vector<int>> G(n+1);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    root = -1;
    for (int u = 1; u <= n; u++) if (D[u] == 1) { root = u; break; }
    if (root == -1) { cout << 0 << endl; return 0; }

    children.assign(n+1, {});
    vector<int> parent(n+1, -1);
    queue<int> Q;
    Q.push(root);
    parent[root] = -1;

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int v : G[u]) {
            if (parent[v] != -1 or v == parent[u]) continue;
			parent[v] = u;
			children[u].push_back(v);
			Q.push(v);
        }
    }

    int l = 0, h = n;
    int answer = h;
    while (l <= h) {
        int mid = (l+h)/2;
        if (check(mid)) {
            answer = mid;
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << answer << endl;

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
	test("ex2");
	test("ex3");
	return 0;
}
#endif
