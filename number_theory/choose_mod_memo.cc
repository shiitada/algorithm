/*
  Binomial coefficient modulo prime (memorization)
  素数を法とした二項係数（メモ化）
  =================================

  # Description
    素数を法とした，階乗・階乗の逆元・k-階乗・二項係数・多重集合係数を求める

    Combination cm(N); : 0 から N までの階乗とその逆元を O(N) 時間で求める（0! = 1）
      + ModInt fact[i]  : iの階乗 i! = 1 * 2 * ... * i  (0 <= i <= N)
      + ModInt inv_f[i] : iの階乗の逆元 (i!)^-1  (0 <= i <= N)
    除数 ModInt::mod は素数で N < ModInt::mod とする（∵ 素数でないと逆元が存在しない場合がある）

    各メソッドは定数時間で呼び出し可能
      + Factorial(n) : nの階乗(factorial) n!
      + InvFactorial(n) : nの階乗の逆元 (n!)^-1
      + Permutation(n, k) : k-permuation of n P(n, k) = n * (n - 1) * ... * (n - k + 1)
      + Choose(n, k) : 二項係数(binomial coefficeint) \binom{n}{k} = n! / k! * (n-k)!
      + MultiChoose(n, k) : 多重集合係数(multiset coefficient) = \binom{n + k - 1}{k}

  # Note
    - ./modular_arithmetics.cc をインクルードする
    - 多重集合係数を使用するときはサイズを2倍にする(n + k - 1 <= 2n - 1)

  # References
    - [@保坂和宏 プログラミングコンテストでの数え上げ&整数論テクニック]
      (http://hos.ac/slides/20130319_enumeration.pdf)
    - [@tubo28 n!,nPr,nCr,nHr構造体](http://tubo28.me/algorithm/comb/)

  # Verified
    - [yukicoder No.117 組み合わせの数](https://yukicoder.me/problems/no/117)

*/

#include <iostream>
#include <vector>

//  @require ./modular_arithmetics.cc 👇👇

// -------------8<------- start of library -------8<------------------------
struct Combination {
    const Int mod = ModInt::mod, N;
    std::vector<ModInt> fact, inv_f;

    // MultiChoose を使用する場合は N = 2 * _n とする
    Combination(int _n) : N(_n < mod ? _n : mod - 1), fact(N + 1), inv_f(N + 1) {
        fact[0] = 1;
        for (int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * i;
        inv_f[N] = fact[N].inv();
        for (int i = N; 1 <= i; --i) inv_f[i - 1] = inv_f[i] * i;
    }

    ModInt Factorial(const int n) const { return fact[n]; }
    ModInt InvFactorial(const int n) const { return inv_f[n]; }

    ModInt Permutation(const int n, const int k) const {
        if (k < 0 || n < k) return ModInt(0);
        else return fact[n] * inv_f[n - k];
    }
    ModInt Choose(const int n, const int k) const {
        if (n < 0 || k < 0 || n < k) return ModInt(0);
        else return fact[n] * inv_f[k] * inv_f[n - k];
    }
    ModInt MultiChoose(const int n, const int k) const {
        if (n < 0 || k < 0) return ModInt(0);
        else return k == 0 ? 1 : Choose(n + k - 1, k);
    }
};
// -------------8<------- end of library ---------8-------------------------

int main() {
    Combination cm(2 * 1e6);

    int T, n, k;
    char c;
    scanf("%d\n", &T);

    while (T--) {
        scanf("%c(%d,%d)\n", &c, &n, &k);
        if (c == 'C') printf("%d\n", cm.Choose(n, k).v);
        else if (c == 'P') printf("%d\n", cm.Permutation(n, k).v);
        else if (c == 'H') printf("%d\n", cm.MultiChoose(n, k).v);
    }

    return 0;
}
