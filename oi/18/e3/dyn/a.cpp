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


int run(istream &cin, ostream &cout) {
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

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	test("ex2");
	test("ex3");
	return 0;
}
#endif
