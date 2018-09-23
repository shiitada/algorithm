/*
  Modular Arithmetics
  ===================

  # Description
    ここでは，ModInt::mod による剰余の基本的な演算を扱う（@tmaeharaさんの実装を参考）

    - Int : 整数の型．実行時間がシビアでない場合はlong long型を使う
    - Int ModInt::mod : 除数．競プロでは素数（∵ 逆元が存在する）
    - Int ModInt::v : [0, mod) の範囲にある整数

    ModInt x; m = ModInt::mod;
    - 加算・減算・乗算・比較 : 定数時間
    - x.inv() : x の逆元（x と m 互いに素のときに存在）
                O(log m) 時間．除算 / はこの演算を呼び出している．
    - x.pow(e) : 冪乗の剰余 x^e mod m を計算．
                 O(log e) 時間．繰り返し２乗法を用いている．

  # Note
    ModInt同士の積はInt型ではオーバーフローするので，一時的にgcc拡張の __uint128_t へキャストしている．
      + long long: 10^18 < 2^63 - 1 < 10^19
      + __int128_t: 10^38 < 2^127 - 1 < 10^39

  # References
    - [@保坂和宏 プログラミングコンテストでの数え上げ&整数論テクニック]
      (http://hos.ac/slides/20130319_enumeration.pdf)
    - [@tubo28 MOD取り構造体](http://tubo28.me/algorithm/mint/)
    - [@tmaehara spagetthi-source modular_arithmetics.cc]
      (https://github.com/spaghetti-source/algorithm/blob/master/number_theory/modular_arithmetics.cc)

  # Verified
    - x.pow() の Verified
      [AOJ NTL_1_B](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B)

*/

#include <bits/stdc++.h> // Replace needed headers for speed up

// -------------8<------- start of library -------8<------------------------
using Int = long long;

struct ModInt {
    static constexpr Int mod = 1e9 + 7; // assume mod is prime
    Int v;

    ModInt(Int _v = 0) : v((_v % mod + mod) % mod) {}

    bool operator<(ModInt r) const { return v < r.v; }
    bool operator>(ModInt r) const { return r.v < v; }
    bool operator==(ModInt r) const { return v == r.v; }
    bool operator!= (ModInt r) const { return v != r.v; }

    ModInt operator-() const { return ModInt(v ? mod - v : v); }
    ModInt &operator+=(ModInt r) { (v += r.v) %= mod; return *this; }
    ModInt &operator-=(ModInt r) { (v -= r.v - mod) %= mod; return *this; }
    ModInt &operator*=(ModInt r) { v = (__uint128_t(v) * r.v) % mod; return *this; }
    ModInt &operator/=(ModInt r) { *this *= r.inv(); return *this; }

    ModInt inv() const {
        Int u = 1, tv = v, s = 0, t = mod;
        while (t) {
            Int q = tv / t;
            std::swap(tv -= q * t, t);
            std::swap(u -= q * s, s);
        }
        return ModInt(u < 0 ? u + mod : u);
    }

    ModInt pow(Int e) {
        ModInt a = *this, x(1);
        for ( ; 0 < e; e >>= 1) { if (e & 1) x *= a; a *= a; }
        return x;
    }
};
ModInt operator+(ModInt l, ModInt r) { return l += r; }
ModInt operator-(ModInt l, ModInt r) { return l -= r; }
ModInt operator*(ModInt l, ModInt r) { return l *= r; }
ModInt operator/(ModInt l, ModInt r) { return l /= r; }
std::ostream &operator<<(std::ostream &os, const ModInt &r) { return os << r.v; }
std::istream &operator>>(std::istream &is, ModInt &r) { is >> r.v; return is; }
// -------------8<------- end of library ---------8-------------------------

int main() {
    Int n;
    ModInt m;
    std::cin >> m >> n;
    std::cout << m.pow(n) << std::endl;

    return 0;
}
