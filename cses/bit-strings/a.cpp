#include <iostream>
#include <vector>

#ifdef DEBUG
#include <print>
#include <fstream>
#include <sstream>
#endif

using namespace std;

typedef unsigned long long ll;

int run(istream &cin, ostream &cout) {
	int n;
	cin >> n;

	const ll MOD = 1e9 + 7;

	ll val = 1;
	ll a = 2;
	ll b = n;
	while (b > 0) {
		if (b & 1)
			val = val * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}

	cout << val << endl;

	return 0;
}


#ifdef DEBUG

string rtrim(const string &s) {
	size_t end = s.find_last_not_of(" \n\r\t\f\v");
	return (end == string::npos) ? "" : s.substr(0, end + 1);
}

void tf(string name) {
	ifstream in(format("{}.in", name));
	ostringstream out;
	
	ifstream exp(format("{}.out", name));
	string expStr(istreambuf_iterator<char>{exp}, {});
	expStr = rtrim(expStr);

	run(in, out);
	string outStr = rtrim(out.str());

	if (outStr != expStr) {
		print("test {} failed! expected: \n'{}'\n--- got \n'{}'\n", name, expStr, outStr);
	} else {
		print("test {} success\n", name);
	}
}

int main() {
	tf("ex0");
	tf("ex1");
	return 0;
}
#else
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	return run(cin, cout);
}
#endif
