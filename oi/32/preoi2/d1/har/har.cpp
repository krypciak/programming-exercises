#include "harlib.h"

#include <bits/stdc++.h>

using namespace std;

vector<int> Pomaluj(int n, int m, int A, int B, vector<int> U, vector<int> V) {
	vector<int> kolory(m, -1);

	vector<vector<pair<int, int>>> G(n);
	for (int i = 0; i < m; i++) {
		int f = U[i], t = V[i];
		G[f].push_back({t, i});
		G[t].push_back({f, i});
	}

	vector<int> seq;
	if (A >= 3) {
		seq = {0, 1, 2};
	} else {
		seq = {0, 1, 0, 0, 1, 1};
	}
	vector<bool> visited(n, false);
	vector<int> toVisit{0};
	visited[0] = true;
	for (int dist = 0; toVisit.size(); dist++) {
		vector<int> nextToVisit;
		nextToVisit.reserve(toVisit.size()*2);
		for (int v : toVisit) {
			for (auto [u, um] : G[v]) {
				if (kolory[um] == -1) kolory[um] = seq[dist % seq.size()];
				if (visited[u]) continue;
				visited[u] = true;
				nextToVisit.push_back(u);
			}
		}
		toVisit = nextToVisit;
	}
	return kolory;
}

int A, B;
void Init(int A1, int B1) {
	A = A1;
	B = B1;
}

int last = -1;
int looking = 0;
vector<int> lookHist;

#ifdef TEST
bool debug = true;
#else
bool debug = false;
#endif

int sub2dec(const vector<int> &y) {
	if (debug) cout << y[0] << endl;
	if (debug) cout << y[1] << endl;
	if (looking > 0) { 
		looking++;
		int ret;
		if (y[0] >= 1) {
			assert(y[1] == 0);
			lookHist.push_back(0);
			ret = 0;
		} else if (y[1] >= 1) {
			assert(y[0] == 0);
			lookHist.push_back(1);
			ret = 1;
		} else assert(false);

		if (looking <= 3 or looking == 5 or looking == 6) return ret;
		if (looking == 4) return -1;

		if (looking == 7) {
			if (debug) {
			cout << "looking end" << endl;

			for (int i = 0; i < (int)lookHist.size(); i++) {
				cout << lookHist[i] << " ";
			}
			std::cout<<endl;
			}

			string path = "";
			path += (char)lookHist[7]+'0';
			path += (char)lookHist[6]+'0';
			path += (char)lookHist[2]+'0';
			path += (char)lookHist[3]+'0';
			path += (char)lookHist[4]+'0';

			string toSearch = "010011010011010011";

			if (debug) cout << path << endl;
			if (debug) cout << endl;
			looking = 0;
			if (toSearch.find(path) != string::npos) {
				// initial dir was wrong
				return ret;
			} else {
				// initial dir was right
				return -1;
			}
		}
		return -2137;
	}
	if (y[0] == 1 and (y[1] >= 2 or y[1] == 0)) return 0;
	if ((y[0] >= 2 or y[0] == 0) and y[1] == 1) return 1;

	if ((y[0] == 1 and y[1] == 1) or (y[0] == 0 and y[1] == 2) or (y[0] == 2 and y[1] == 0)) {
		if (last == -1) {
			assert(last == -1);
			looking = 1;
			if (debug) cout << "looking" << endl;

			lookHist.push_back(0);
			lookHist.push_back(1);
			if (y[0] >= 1) return 0;
			else return 1;

		} else if (last == 0) return 1;
		else return 0;
	} else {
		if (y[0] == 1) return 0;
		if (y[1] == 1) return 0;
	}
	assert(false);
}

int Rusz(vector<int> y) {
	if (A >= 3) {
		if (y[0] >= 1 and y[1] == 0 and y[2] == 0) return 0;
		if (y[0] == 0 and y[1] >= 1 and y[2] == 0) return 1;
		if (y[0] == 0 and y[1] == 0 and y[2] >= 1) return 2;
		
		if (y[0] >= 1 and y[1] >= 1) return 0;
		if (y[1] >= 1 and y[2] >= 1) return 1;
		if (y[2] >= 1 and y[0] >= 1) return 2;
	} else {
		int to = sub2dec(y);
		if (debug) std::cout << "going to " << to << endl;
		last = to;
		if (debug) cout << endl;
		return to;
	}
	return -1;
}
