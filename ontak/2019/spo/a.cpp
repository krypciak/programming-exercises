#include <vector>
#include <iostream>
#include <cassert>
#include <queue>

#ifdef DEBUG
#include <print>
#include <sstream>
#include <fstream>
#endif

using namespace std;

#ifdef DEBUG
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, s, t;
	cin >> n >> m >> s >> t;
	assert(1 <= n && n <= 100000);
	assert(1 <= m && m <= 500000);
	assert(s != t && 1 <= s && s <= n && 1 <= t && t <= n);
	s--;
	t--;

	typedef long long ll;
	typedef pair<ll, int> pt;
	typedef vector<vector<pt>> gt;
	gt graph(n);
	gt graphRev(n);
	for (int i = 0; i < m; i++) {
		int from, to;
		ll len;
		cin >> from >> to >> len;
		from--;
		to--;
		graph[from].push_back({len, to});
		graphRev[to].push_back({len, from});
	}

	auto dij = [n](const gt &graph, int from, int to) -> vector<ll> {
		priority_queue<pt, vector<pt>, greater<pt>> q;
		q.push({0, from});
		vector<ll> dist(n, 2e9);
		while (!q.empty()) {
			auto [len, to] = q.top();
			q.pop();

			if (len >= dist[to]) continue;

			dist[to] = len;
			for (auto [len1, to1] : graph[to]) {
				ll nl = len + len1;
				if (nl < dist[to1]) {
					q.push({nl, to1});
				}
			}
		}
		return dist;
	};

	vector<ll> distSt = dij(graph, s, t);
	ll shortestSt = distSt[t];

	vector<ll> distTs = dij(graphRev, t, s);

	auto check = [&]() -> bool {
		for (int i = 0; i < n; i++) {
			for (auto [len, to] : graph[i]) {
				if (distSt[i] + len + distTs[to] == shortestSt + 1) {
					return true;
				}
			}
		}
		return false;
	};
	if (check()) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}


	return 0;
}

#ifdef DEBUG
string rtrim(const string &str) {
	size_t end = str.find_last_not_of(" \n\r\t\f\v");
	return (end == string::npos) ? str : str.substr(0, end + 1);
}
int test(string name) {
	ifstream in(format("{}.in", name));
	ostringstream out;

	ifstream exp(format("{}.out", name));
	string expStr(istreambuf_iterator<char>{exp}, {});
	expStr = rtrim(expStr);

	run(in, out);
	string outStr = rtrim(out.str());

	if (outStr != expStr) {
		print("\u001b[1m\u001b[31mx\u001b[0m\u001b[22m {} expected: \n'{}'\n---got:\n'{}'\n\n", name, expStr, outStr);
	} else {
		print("\u001b[1m\u001b[32m\u221A\u001b[0m\u001b[22m {}\n", name);
	}

	return 0;
}
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
