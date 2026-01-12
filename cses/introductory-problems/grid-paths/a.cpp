#include <bits/stdc++.h>
using namespace std;

string str;
vector<int> forceDirs;
const int w = 9, h = 9;
auto visited = vector<vector<char>>(h, vector<char>(w, false));
int sum = 0;
int steps = 0;
const vector<int> dx{0, 0, -1, 1};
const vector<int> dy{-1, 1, 0, 0};

void rec(int x, int y) {
	if (x == 1 && y == 7) {
		if (steps == 48) sum++;
		return;
	}


	if ((!visited[y][x-1] && !visited[y][x+1] && visited[y+1][x] && visited[y-1][x]) ||
	    (!visited[y-1][x] && !visited[y+1][x] && visited[y][x+1] && visited[y][x-1])) return;

	visited[y][x] = true;
	int force = forceDirs[steps];
	for (int d = (force == -1) ? 0 : force; (force == -1) ? (d < 4) : d == force; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (visited[ny][nx]) continue;

		steps++;
		rec(nx, ny);
		steps--;

		if (force != -1) break;
	}
	visited[y][x] = false;
}

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> str;

	forceDirs = vector<int>(str.size(), -1);

	for (int i = 0; i < (int)str.size(); i++) {
		char c = str[i];
		if (c != '?') {
			forceDirs[i] = c == 'U' ? 0 :
				       c == 'D' ? 1 :
				       c == 'L' ? 2 :
				       c == 'R' ? 3 :
				       throw invalid_argument("what");
		}
	}

	for (int y = 0; y < h; y++) { visited[y][0] = true; visited[y][w-1] = true; }
	for (int x = 0; x < w; x++) { visited[0][x] = true; visited[h-1][x] = true; }

	rec(1, 1);
	cout << sum << endl;

	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif
