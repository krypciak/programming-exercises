#include <iostream>

#ifdef DEBUG
#include <print>
#include <fstream>
#include <sstream>
#endif

using namespace std;

typedef long long ll;

int run(istream &cin, ostream &cout) {
	int t;
	cin >> t;

	auto spiral = [](ll y) -> ll {
		if (y == 0) return 1;

		ll val = y - ((y % 2 == 0) ? 1 : 0);
		val = (val+1) * (val+1);
		if (y % 2 == 0) val++;
		return val;
	};

	for (int i = 0; i < t; i++) {
		ll y, x;
		cin >> y >> x;
		x--;
		y--;

		ll val;
		if (x > y) {
			if (x % 2 == 0) val = spiral(x) + (x + x - y);
			else val = spiral(x) - (x + x - y);
		} else {
			if (y % 2 == 0) val = spiral(y) + x;
			else val = spiral(y) - x;
		}
		cout << val << endl;
	}
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
	return 0;
}
#else
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	return run(cin, cout);
}
#endif
