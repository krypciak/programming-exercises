#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

struct Seg {
    int n;
    vector<ll> t;
    vector<ll> lazy;
    int h;
    
    Seg(const vector<ll> &a) {
        n = bit_ceil(a.size());
        t.assign(n*2, 0);
        lazy.assign(n, 0);

        h = 31-countl_zero((unsigned int)n);
        for (int i = n; i < n+(int)a.size(); i++) t[i] = a[i-n];
        for (int i = n-1; i > 0; i--) t[i] = t[i<<1]+t[i<<1|1];
    }

    void apply(int p, ll v, ll mul) {
        t[p] += v*mul;
        if (p < n) lazy[p] += v;
    }

    void build(int p) {
        ll len = 1;
        while (p > 1) {
            p >>= 1;
            t[p] = t[p<<1] + t[p<<1|1] + (lazy[p]<<len);
            len++;
        }
    }

    void push(int p0) {
        for (int i = h; i >= 1; i--) {
            int p = p0 >> i;
            if (lazy[p]) {
                apply(p<<1, lazy[p], 1LL<<(i-1));
                apply(p<<1|1, lazy[p], 1LL<<(i-1));
                lazy[p] = 0;
            }
        }
    }

    ll query(int l, int r) {
        l += n, r += n;
        push(l);
        push(r-1);
        ll res = 0;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += t[l++];
            if (r&1) res += t[--r];
        }
        return res;
    }

    void inc(int l, int r, ll v) {
        l += n, r += n;
        int l0 = l, r0 = r;
        for (ll len = 1; l < r; l >>= 1, r >>= 1, len <<= 1) {
            if (l&1) apply(l++, v, len);
            if (r&1) apply(--r, v, len);
        }
        build(l0);
        build(r0-1);
    }
};

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
    ios_base::sync_with_stdio(0), cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    Seg seg(a);

    while (m--) {
        int t, l, r;
        cin >> t >> l >> r;
        l--;
        if (t == 1) {
            auto res = seg.query(l, r);
            cout << res << '\n';
        } else {
            int a;
            cin >> a;
            seg.inc(l, r, a);
        }
    }
    return 0;
}

#ifdef TEST
string rtrim(string str) {
    auto end = str.find_last_not_of(" \n\r\f\v\t");
    return end == string::npos ? str : str.substr(0, end+1);
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
int main() {
    test("ex0");
    test("ex1");
    test("ex2");

    for (int i = 0; i < 1; i++) test(format("gen/{}", i));
    return 0;
}
#endif
