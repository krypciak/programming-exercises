#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#ifdef TEST
#include <print>
#include <fstream>
#include <sstream>

int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	vector<int> ent(n);
	vector<int> lea(n);
	for (int i = 0; i < n; i++) {
		cin >> ent[i] >> lea[i];
	}
	sort(ent.begin(), ent.end());
	sort(lea.begin(), lea.end());

	int i = 0, j = 0;
	int custMax = 0;
	int cust = 0;
	while (i < n) {
		if (ent[i] <= lea[j]) {
			i++;
			cust++;
			custMax = max(custMax, cust);
		} else {
			j++;
			cust--;
		}
	}
	cout << custMax << endl;
	return 0;
}

#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \n\r\t\v\f");
	return end == string::npos ? s : s.substr(0, end+1);
}
bool printT(string name, string expS, string outS) {
	if (expS == outS) {
		print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name, expS, outS);
	} else {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} fail! expected: \n'{}'\n---got: \n'{}'\n\n", name, expS, outS);
	}
	return expS == outS;
}
void test(string name) {
	ifstream in(name + ".in");
	ostringstream out;

	ifstream exp(name + ".out");
	string expS(istreambuf_iterator<char>{exp}, {});
	expS = rtrim(expS);

	run(in, out);

	string outS = rtrim(out.str());
	printT(name, expS, outS);
}
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
