#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
 
using namespace std;
typedef unsigned long long ll;
 
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
 
	int q;
	cin >> q;
 
	auto pow10 = [](int to) {
		ll res = 1;
		for (int i = 0; i < to; i++) res *= 10;
		return res;
	};
 
	for (int qi = 0; qi < q; qi++) {
		ll k;
		cin >> k;
 
		int i = 1;
		for (;; i++) {
			ll sub = i*9 * pow10(i-1);
			if (k <= sub) break; 
			k -= sub;
		}
 
		long num = (k - 1) / i + pow10(i - 1);
		int loc = (int)((k - 1) % i);
		cout << to_string(num)[loc] << endl;
	}
	return 0;
}
 
#ifdef TEST
string rtrim(const string &s) {
	auto end = s.find_last_not_of(" \n\r\t\v\f");
	return end == string::npos ? s : s.substr(0, end+1);
}
bool printRes(const string& name, const string &expStr, const string &outStr, bool printSuccess = true) {
	if (outStr != expStr) {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} failed! expected:\n'{}'\n----got:\n'{}'\n\n", name, expStr, outStr);
		return false;
	} else {
		if (printSuccess) print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
		return true;
	}
}
void test(const string &name) {
	ifstream in(format("{}.in", name));
	ostringstream out;
 
	ifstream exp(format("{}.out", name));
	string expStr(istreambuf_iterator<char>{exp}, {});
	expStr = rtrim(expStr);
 
	run(in, out);
	string outStr = rtrim(out.str());
	printRes(name, expStr, outStr);
}
void fuzz() {
	const int N = 4;
	string str = " ";
	for (int i = 0; i < N; i++) {
		for (ll v = pow(10, i); v < pow(10, i+1); v++) {
			str += to_string(v);
		}
	}
 
	int k;
	for (k = 1; k < (int)str.size(); k++) {
		istringstream in(format("1\n{}", k));
		ostringstream out;
		run(in, out);
		string resStr = rtrim(out.str());
 
		if (!printRes(format("fuzz k: {}", k), format("{}", str[k]), resStr, false)) {
			const int from = 10;
			const int to = 10;
			for (int j = k - from; j < k + to; j++) cout << j << '\t';
			cout << endl;
			for (int j = k - to; j < k + from; j++) cout << str[j] << '\t';
			cout << endl;
			break;
		}
		if (k % 1000000 == 0) {
			print("{} / {}\n", k, str.size());
		}
	}
	if (k == (int)str.size()) {
		printRes("fuzz all", "", "");
	}
}
int main() {
	test("ex0");
	test("ex1");
	fuzz();
	return 0;
}
#endif
