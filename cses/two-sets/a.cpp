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

	if (n % 4 == 1 or n % 4 == 2) {
		cout << "NO" << endl;
		return 0;
	}

	vector<int> set1;
	vector<int> set2;

	if (n % 4 == 3) {
		for (int i = 1; i < n / 4 + 1; i++) {
			set1.push_back(i);
			set1.push_back(n - i);
		}
		set1.push_back(n);

		for (int i = n / 4 + 1; i < n / 2 + 1; i++) {
			set2.push_back(i);
			set2.push_back(n - i);
		}
	} else if (n % 4 == 0) {
		for (int i = 1; i < n / 4 + 1; i++) {
			set1.push_back(i);
			set1.push_back(n - i + 1);
		}
		for (int i = n / 4 + 1; i < n / 2 + 1; i++) {
			set2.push_back(i);
			set2.push_back(n - i + 1);
		}

	}

	cout << "YES" << endl;
	cout << set1.size() << endl;
	for (int i = 0; i < (int)set1.size(); i++) {
		if (i > 0) cout << " ";
		cout << set1[i];
	}
	cout << endl;
	cout << set2.size() << endl;
	for (int i = 0; i < (int)set2.size(); i++) {
		if (i > 0) cout << " ";
		cout << set2[i];
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
	tf("ex7");
	tf("ex5");
	tf("ex4");
	tf("ex8");
	return 0;
}
#else
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	return run(cin, cout);
}
#endif
