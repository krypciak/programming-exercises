#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

struct Seg {
    int n;
    vector<ll> t;
    vector<ll> lazy;
    int h;

    ll comb(ll a, ll b) { return max(a, b); }

    Seg(const vector<int> &arr) {
        n = bit_ceil(arr.size());
        t.assign(n*2, 0);
        lazy.assign(n, 0);
        h = bit_width((unsigned int)n);
        
        for (int i = 0; i < (int)arr.size(); i++) t[i+n] = arr[i];
        for (int i = n-1; i > 0; i--) t[i] = comb(t[i<<1], t[i<<1|1]);
    }

    void apply(int p, ll v) {
        t[p] += v;
        if (p < n) lazy[p] += v;
    }

    void build(int p) {
        while (p > 1) {
            p >>= 1;
            t[p] = comb(t[p<<1], t[p<<1|1]) + lazy[p];
        }
    }

    void push(int p0) {
        for (int s = h-1; s >= 1; s--) {
            int p = p0 >> s;
            if (lazy[p]) {
                apply(p<<1, lazy[p]);
                apply(p<<1|1, lazy[p]);
                lazy[p] = 0;
            }
        }
    }

    void inc(int l, int r, ll v) {
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
        l += n, r += n;
        push(l);
        push(r-1);
        ll res = LLONG_MIN;
        for (; l < r; l>>=1, r>>=1) {
            if (l&1) res = comb(res, t[l++]);
            if (r&1) res = comb(res, t[--r]);
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
        int t; 
        cin >> t;
        int l, r;
        cin >> l >> r;
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
    test("ex0");
    test("ex1");
    test("ex2");
    return 0;
}
#endif
