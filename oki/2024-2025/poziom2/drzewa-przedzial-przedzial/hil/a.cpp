#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

const ll MOD = 123456789;
struct Seg {
    int n;
    vector<ll> t;
    vector<ll> lazy;
    int h;

    ll mul(ll a, ll b) { return (a*b)%MOD; }
    ll add(ll a, ll b) { return (a+b)%MOD; }

    Seg(const vector<int> &arr) {
        n = bit_ceil(arr.size());
        t.assign(n*2, 0);
        lazy.assign(n, 1);
        h = bit_width((unsigned int)n);

        for (int i = 0; i < (int)arr.size(); i++) t[i+n] = arr[i];
        for (int i = n-1; i; i--) t[i] = add(t[i<<1], t[i<<1|1]);
    }

    void apply(int p, ll v) {
        t[p] = mul(t[p], v);
        if (p < n) lazy[p] = mul(lazy[p], v);
    }

    void build(int p) {
        while (p > 1) {
            p >>= 1;
            t[p] = mul(add(t[p<<1], t[p<<1|1]), lazy[p]);
        }
    }

    void push(int p0) {
        for (int s = h-1; s >=1; s--) {
            int p = p0 >> s;
            if (lazy[p] != 1) {
                apply(p<<1, lazy[p]);
                apply(p<<1|1, lazy[p]);
                lazy[p] = 1;
            }
        }
    }

    void inc(int l, int r, ll v) {
        v %= MOD;
        l += n, r += n;
        int l0 = l, r0 = r;
        for (; l < r; l>>=1, r>>=1) {
            if (l&1) apply(l++, v);
            if (r&1) apply(--r, v);
        }
        build(l0);
        build(r0-1);
    }

    ll query(int l, int r) {
        ll res = 0;
        l += n, r += n;
        push(l);
        push(r-1);
        for (; l < r; l>>=1, r>>=1) {
            if (l&1) res = add(res, t[l++]);
            if (r&1) res = add(res, t[--r]);
            if (res < 0) res += MOD;
        }
        return res;
    }
};

int run(istream &cin, ostream &cout) {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
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
            #ifdef TEST
            assert(t == 2);
            #endif
            int v;
            cin >> v;
            seg.inc(l, r, v);
        }
    }

    return 0;
}


#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
    test("ex2");
    test("ex0");
    test("ex1");
    return 0;
}
#endif
