#include <bits/stdc++.h>
using namespace std;


struct Vec2 {
	int x, y;
};

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	cin >> n;
	vector<vector<int>> map(n, vector<int>(n));
	for (int y = 0; y < n; y++) for (int x = 0; x < n; x++) cin >> map[y][x];


	vector<vector<bool>> visited(n, vector<bool>(n, false));

	int dol = 0;
	int grzb = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			if (visited[y][x]) continue;

			int v = map[y][x];
			vector<Vec2> toVisit{{x, y}};
			visited[y][x] = true;
			int isLowerG = -1;
			while(toVisit.size()) {
				vector<Vec2> nextToVisit;
				nextToVisit.reserve(toVisit.size()*4);
				for (auto [x, y] : toVisit) {
					for (int y1 = max(0, y-1); y1 < min(n, y+2); y1++) {
						for (int x1 = max(0, x-1); x1 < min(n, x+2); x1++) {
							if (y1 == y && x1 == x) continue;
							int v1 = map[y1][x1];
							if (v == v1) {
								if (visited[y1][x1]) continue;
								visited[y1][x1] = true;
								nextToVisit.push_back({x1, y1});
							} else {
								if (isLowerG == 2) continue;
								bool isLower = v > v1;
								if (isLowerG == -1) isLowerG = isLower;
								else if (isLower != isLowerG) {
									isLowerG = 2;
								}
							}
						}
					}
				}
				toVisit = nextToVisit;
			}
			if (isLowerG == 0 || isLowerG == -1) dol++;
			if (isLowerG == 1 || isLowerG == -1) grzb++;
		}
	}
	cout << grzb << ' ' << dol << endl;
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
	test("ex1");
	test("ex0");
	return 0;
}
#endif
