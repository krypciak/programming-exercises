#include <bits/stdc++.h>
using namespace std;

struct Vec2 {
	int x, y;
};

int run(istream &cin, ostream &cout) {
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

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
	test("ex1");
	test("ex0");
	return 0;
}
#endif
