#include <bits/stdc++.h>

using namespace std;

int run(istream &cin, ostream &cout) {
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


#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif

