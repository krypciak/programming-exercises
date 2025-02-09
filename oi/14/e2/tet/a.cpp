#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

	uint n;
	cin >> n;

	const uint MAXN = 50000+1;
	const uint MAXNN = MAXN*2;

	uint S[MAXNN]; int Si = n*2-1;
	for (int i = n*2-1; i >= 0; i--) cin >> S[i];


	uint D[MAXNN]; uint Di = 0;
	char DS[MAXN+1]; memset(DS, false, MAXN+1);

	uint output[1000001]; uint outputI = 0;
	ostringstream out;

	while(Si >= 0) {
		uint x = S[Si--];
		if (DS[x] == false) { 
			D[++Di] = x;
			DS[x] = true;
		} else {
			uint y = D[Di--];
			DS[y] = false;
			if (x != y) {
				output[outputI++] = Di+1;
				S[++Si] = y;
				S[++Si] = x;
			}
		}
	}
	cout << outputI << '\n';
	for (uint i = 0; i < outputI; i++) cout << output[i] << '\n';
	return 0;
}
#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \t\r\v\f\n");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string expS, string outS) {
	if (expS == outS)
	printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
	else
	printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: \n'%s'\n-----got: \n'%s'\n\n", name.c_str(), expS.c_str(), outS.c_str());
}
void test(string name) {
	ifstream in(name+".in");
	ostringstream out;
	run(in, out);
	string outS = rtrim(out.str());

	ifstream exp(name+".out");
	string expS(istreambuf_iterator<char>{exp}, {});
	expS = rtrim(expS);

	printT(name, expS, outS);
}
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
