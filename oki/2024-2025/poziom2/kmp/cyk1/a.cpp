#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	string s;
	{
		string g;
		cin >> n >> s >> g;

		s += "#" + g + g;
	}

	vector<int> kmp(s.size()+1);
	kmp[0] = -1;
	int t = -1;

	for (int i = 0; i < (int)s.size(); i++) {
		while (t >= 0 and s[t] != s[i]) t = kmp[t];
		kmp[i+1] = ++t;
		if (t == n) {
			cout << "TAK" << '\n';
			return 0;
		}
	}
	cout << "NIE" << '\n';
	return 0;
}
#ifdef TEST
int n;
const ll M = 1e9 + 21;
const ll BASE = 31;
vector<ll> MUL;

int cti(char c) { return c-'a'+1; }

ll hashOf(const string &s) {
	ll h = 0;
	for (int i = 0; i < n; i++)
		h = (h + MUL[i]*cti(s[i])%M) % M;
	return h;
}

int brute(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string a, b;
	cin >> n;
	cin >> a >> b;

	MUL.assign(n*2, 0);
	MUL[0] = 1;
	for (int i = 1; i < n*2; i++) MUL[i] = (MUL[i-1] * BASE) % M;

	ll aHash = hashOf(a);
	ll bHash = hashOf(b);

	a += a;
	if (bHash == aHash) { cout << "TAK" << '\n'; return 0; }

	for (int i = n; i < n*2; i++) {
		aHash = (aHash - (MUL[i-n]*cti(a[i-n])%M) + M) % M;
		aHash = (aHash + (MUL[i]*cti(a[i])%M)) % M;

		bHash = (bHash * BASE) % M;
		if (bHash == aHash) { cout << "TAK" << '\n'; return 0; }
	}
	cout << "NIE" << '\n';
	return 0;
}

string rtrim(string s) {
	auto end = s.find_last_not_of(" \n\r\t\f\v");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string outS, string expS) {
	if (outS == expS) {
		print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
	} else {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} fail! expected: \n'{}'\n---got: \n'{}'\n\n", name, expS, outS);
	}
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
void testBrute() {
	for (int i = 0; i < 100; i++) {
		int n = 1000;
		string inp = to_string(n) + "\n";
		for (int i = 0; i < n; i++) inp += (char)('a' + rand()%26);
		inp += "\n";
		for (int i = 0; i < n; i++) inp += (char)('a' + rand()%26);

		istringstream in(inp);
		ostringstream out;
		run(in, out);
		string outS = rtrim(out.str());

		istringstream in1(inp);
		ostringstream out1;
		run(in1, out1);
		string out1S = rtrim(out1.str());

		if (outS != out1S) {
			printT("brute " + to_string(i), out1S, outS);
			break;
		}
	}
	cout << "brute done" << endl;
}
int main() {
	test("ex0");
	test("ex1");
	test("ex2");
	test("ex3");
	testBrute();
	return 0;
}
#endif
