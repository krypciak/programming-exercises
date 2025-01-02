#include <iostream>
#include <vector>

#ifdef DEBUG
#include <print>
#include <fstream>
#include <sstream>
#endif

using namespace std;

int run(istream &cin, ostream &cout) {
	int n;
	cin >> n;

	if (n == 2 or n == 3) {
		cout << "NO SOLUTION" << endl;
		return 0;
	}

	for (int i = 2; i <= n; i+=2) {
		cout << i << " ";
	}
	for (int i = 1; i <= n; i+=2) {
		cout << i << " ";
	}
	cout << endl;
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
