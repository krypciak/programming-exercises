#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	cin >> n;

	const int MAXA = 500002;
	vector<bool> taken(MAXA, false);
	vector<int> bound(MAXA, -1);
	struct Seq {
		int start, end;
	};
	vector<Seq> seqs;
	seqs.reserve(MAXA/2);

	int score = 0;
	while(n--) {
		int x;
		cin >> x;

		if (taken[x]) {}
		else {
			taken[x] = true;
			int bl = bound[x-1];
			int br = bound[x+1];

			if (bl == -1 and br == -1) {
				score++;
				bound[x] = seqs.size();
				seqs.push_back({x, x});
			} else if (br == -1) {
				seqs[bl].end = x;
				bound[x] = bl;
				int len = seqs[bl].end - seqs[bl].start + 1;
				if (len % 2 == 1) score++; 
			} else if (bl == -1) {
				seqs[br].start = x;
				bound[x] = br;
				int len = seqs[br].end - seqs[br].start + 1;
				if (len % 2 == 1) score++; 
			} else {
				int llen = seqs[bl].end - seqs[bl].start + 1;
				int rlen = seqs[br].end - seqs[br].start + 1;
				if (llen % 2 == 0 and rlen % 2 == 0) score++;

				seqs[bl].end = seqs[br].end;
				bound[seqs[bl].end] = bl;
			}
		}
		cout << score << ' ';
	}
	return 0;
}

#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \r\t\v\f\n");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string outS, string expS) {
	if (outS == expS) 
	printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
	else
	printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: \n'%s'\n---got:\n'%s'\n\n", name.c_str(), expS.c_str(), outS.c_str());
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
	test("ex4");
	test("ex5");
	return 0;
}
#endif
