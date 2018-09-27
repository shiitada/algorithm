/*
  Basic Modular Arithmetics
  基本的な剰余演算
  =========================

  # Description
    ModInt::mod による剰余の基本的な演算を扱う（@tmaeharaさんの実装を参考）

    - Int : 整数の型．実行時間がシビアでない場合はlong long型を使う
    - Int ModInt::mod : 除数．素数ならば[0, mod)の整数は逆元を持つ
    - Int ModInt::v : [0, mod) の範囲にある整数

    ModInt x; m = ModInt::mod;
    - 加算・減算・乗算・比較 : 定数時間
    - x.inv() : x の逆元（x と m 互いに素のときに存在）
    　　　　　　　　拡張ユークリッドの互除法の非再帰版を使用．
                O(log m) 時間．除算 / はこの演算を呼び出している．
    - x.pow(e) : 冪乗の剰余 x^e mod m を計算．
                 O(log e) 時間．繰り返し２乗法を用いている．
    - vector<ModInt> Inverse(n) : 1, 2, ..., n までの逆元をO(n)時間で求める

  # Note
    C/C++ での /, % の仕様
      + a / b : 0に近い整数に丸める (ex. 4 / 3 = 1, -3 / 2 = -1)
      + a % b : aと同じ符号を持つ (eg. 3 % 2 = 1, -3 % 2 = -1, 3 % -2 = 1)
      + a = m * (a / m) + (a % m) が成り立つ

    ModInt::v の初期値として負数が与えられた場合は [0, m) の範囲となるようにする

    ModInt同士の積はInt型ではオーバーフローするので，一時的にgcc拡張の __uint128_t へキャストしている．
      + long long: 10^18 < 2^63 - 1 < 10^19
      + __int128_t: 10^38 < 2^127 - 1 < 10^39
    実際は，__uint128_t は約2倍ぐらい遅いので unsigned long long型へキャストしている．
    競プロでは mod <= int型(2 * 10^9) なので unsigned long long型で収まる．
    もし，mod^2 が int型からオーバーフローするなら __uint128_t型を使う．

    法mに関するaの逆元は拡張ユークリッドの互除法を非再帰で求めている
      拡張ユーリッドの互除法は，整数a, bに対して ax + by = gcd(a, y) を満たす整数x,yを求める問題
      aとmが互いに素ならば gcd(a, m) = 1 となるので，ax + my = 1 を満たす整数x, yを求める
      この等式に対して，法mをとると ax = 1 mod m となり，xがmを法とするaの逆元となる
      逆元が存在するためには，aとmが互い素であることが必要十分条件である

    Inverse(n)は m = i * (m / i) + (m % i) から，1 < i に対して，
      0    ≡ i * (m / i) + (m % i) \mod m  <==>
      i    ≡ -(m / i)^-1 * (m % i) \mod m  <==>
      i^-1 ≡ -(m / i) * (m % i)^-1 \mod m
    となり，(m % i) < i より，再帰的に i の逆元を求める

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

#include <iostream>
#include <vector>

// -------------8<------- start of library -------8<------------------------
using Int = int;

struct ModInt {
    static constexpr Int mod = 1e9 + 7;
    Int v;

    ModInt(long long _v = 0) : v(set(_v)) {}
    ModInt(const ModInt &r) : v(set(r.v)) {}

    inline static Int set(const auto x) { return x < 0 ? (x % mod) + mod : x % mod; }
    inline void set() { v = set(v); }

    bool operator<(ModInt r) const { return v < r.v; }
    bool operator>(ModInt r) const { return r.v < v; }
    bool operator==(ModInt r) const { return v == r.v; }
    bool operator!= (ModInt r) const { return v != r.v; }

    ModInt operator-() const { return ModInt(v ? mod - v : v); }
    ModInt &operator=(const ModInt &r) { if (this != &r) v = set(r.v); return *this; }
    ModInt &operator+=(ModInt r) { (v += r.v) %= mod; return *this; }
    ModInt &operator-=(ModInt r) { (v -= r.v - mod) %= mod; return *this; }
    // ModInt &operator*=(ModInt r) { v = (__uint128_t(v) * r.v) % mod; return *this; }
    ModInt &operator*=(ModInt r) { v = 1ULL * v * r.v % mod; return *this; }
    ModInt &operator/=(ModInt r) { *this *= r.inv(); return *this; }
    ModInt operator+(ModInt r) const { return ModInt(*this) += r; }
    ModInt operator-(ModInt r) const { return ModInt(*this) -= r; }
    ModInt operator*(ModInt r) const { return ModInt(*this) *= r; }
    ModInt operator/(ModInt r) const { return ModInt(*this) /= r; }

    ModInt inv() const {
        long long a = v, b = mod, u = 1, w = 0;
        while (b) {
            long long t = a / b;
            std::swap(a -= t * b, b);
            std::swap(u -= t * w, w);
        }
        return ModInt(u);
    }

    ModInt pow(Int e) {
        ModInt a = *this, x(1);
        for ( ; 0 < e; e >>= 1) { if (e & 1) x *= a; a *= a; }
        return x;
    }
    inline ModInt pow(ModInt &e) { return pow(e.v); }
};
std::ostream &operator<<(std::ostream &os, const ModInt &r) { return os << r.v; }
std::istream &operator>>(std::istream &is, ModInt &r) { is >> r.v; r.set();return is; }

std::vector<ModInt> Inverse(const Int n = ModInt::mod - 1) {
    constexpr Int mod = ModInt::mod;
    std::vector<ModInt> inv(n + 1);
    inv[1].v = 1;
    for (Int a = 2; a <= n; ++a)
        inv[a] = inv[mod % a] * ModInt(mod - mod / a);
    return inv;
}
// -------------8<------- end of library ---------8-------------------------

int main() {
    Int n;
    ModInt m;
    std::cin >> m >> n;
    std::cout << m.pow(n) << std::endl;

    return 0;
}
