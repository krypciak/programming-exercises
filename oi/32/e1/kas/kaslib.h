#include <bits/stdc++.h>
#include <cstdio>

using namespace std;

namespace {
// Można zmienić te wartości.
long long N = 1'000'000'000'000'000'000ll;
int bajtalary = 10'000'000;
bool decreseBajtalar = true;

const int seed = 0;
// Aby zmienić losowość należy zamienić 1 na dowolną inną liczbę typu int.
mt19937_64 rng(seed);

long long X;
bool czy_zainicjalizowany = false;
int wygrane = 0;

long long wylosuj_liczbe() {
  return uniform_int_distribution<long long>(1, N)(rng);
}

void inicjalizuj_gre() {
  X = wylosuj_liczbe();
  // cout << "X: " << X << endl;
}

void inicjalizuj_interakcje() {
  if (czy_zainicjalizowany)
    return;
  inicjalizuj_gre();
  czy_zainicjalizowany = true;
}

constexpr double calcPoints(int w) {
  return (double)floor(100 * ((log2(1 + min(2000, w))) / (log2(1 + 2000))));
}

void proba_zakonczenia() {
  if (!bajtalary) {
    cout << "Liczba wygranych: " << to_string(wygrane) << endl;
    printf("points: %.2f%%\n", calcPoints(wygrane));
    exit(0);
  }
}

void zjedz_bajtalara() {
  proba_zakonczenia();
  if (decreseBajtalar) {
    --bajtalary;
  }
}

void reset() {
  bajtalary = 10'000'000;
  rng = mt19937_64(seed);
  wygrane = 0;
  czy_zainicjalizowany = false;
  inicjalizuj_interakcje();
}

void setRng(int r) { rng = mt19937_64(r); }
} // namespace

long long DajN() {
  inicjalizuj_interakcje();
  return N;
}

long long Pytaj(long long y) {
  inicjalizuj_interakcje();
  assert(1 <= y && y <= N);
  zjedz_bajtalara();
  proba_zakonczenia();
  return __gcd(X, y);
}

void Szturchnij() {
  inicjalizuj_interakcje();
  zjedz_bajtalara();
  X = wylosuj_liczbe();
  proba_zakonczenia();
}

void Odpowiedz(long long y) {
  inicjalizuj_interakcje();
  assert(1 <= y && y <= N);
  zjedz_bajtalara();
  assert(X == y);
  ++wygrane;
  proba_zakonczenia();
  inicjalizuj_gre();
}

void SetX(long long x) {
  X = x;
  printf("// X: %lld\n", X);
}

long long GetX() { return X; }

void Reset() { reset(); }

long long DejBajtalary() { return bajtalary; }

void SetRng(int r) {
  setRng(r);
}