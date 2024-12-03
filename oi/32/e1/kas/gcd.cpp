#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;
int main() {
  while (true) {
    printf("Input:\n");
    ll a, b;
    cin >> a >> b;

    ll gcd = __gcd(a, b);
    printf("%lld\n", gcd);
  }

  return 0;
}
