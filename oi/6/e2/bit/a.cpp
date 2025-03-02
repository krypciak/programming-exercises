#include <bits/stdc++.h>

using namespace std;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int w, h;
	cin >> h >> w;
	vector<string> M(h);
	for (int y = 0; y < h; y++) cin >> M[y];

	vector<vector<int>> D(h, vector<int>(w, INT_MAX));
	vector<pair<int, int>> TV;
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			if (M[y][x] == '1') {
				TV.push_back({x, y});
				D[y][x] = 0;
			}
	
	for (int dist = 1; TV.size(); dist++) {
		vector<pair<int, int>> nTV;
		for (auto [x, y] : TV) {
			const vector<int> aX = {0, 0, 1, -1};
			const vector<int> aY = {1, -1, 0, 0};
			for (int i = 0; i < 4; i++) {
				int nx = x + aX[i];
				int ny = y + aY[i];
				if (nx < 0 or nx >= w or ny < 0 or ny >= h) continue;
				if (D[ny][nx] != INT_MAX) continue;
				D[ny][nx] = dist;
				nTV.push_back({nx, ny});
			}
		}
		TV = nTV;
	}
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			cout << D[y][x];
			if (x != w-1) cout << " ";
		}
		cout << '\n';
	}

	return 0;
}

#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \n\t\f\r\v");
	return end == string::npos ? s : s.substr(0, end+1);
}
bool printTest(string name, string outStr, string expStr) {
	if (outStr == expStr) {
		print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
	} else {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} fail! expected: \n'{}'\n---got: \n'{}'\n\n", name, expStr, outStr);
	}
	return outStr == expStr;
}
void test(string name) {
	ifstream in(name + ".in");
	ostringstream out;

	ifstream exp(name + ".out");
	string expStr(istreambuf_iterator<char>{exp}, {});
	expStr = rtrim(expStr);

	run(in, out);

	string outStr = rtrim(out.str());

	printTest(name, outStr, expStr);
}

int main() {
	test("ex0");
	return 0;
}
#endif

