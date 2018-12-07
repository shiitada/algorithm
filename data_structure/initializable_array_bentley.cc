/*
  Initializable Array by Bentley
  初期化可能な配列
  ==============================

  # Problem
    配列のすべての要素に同一の値を代入する初期化の操作を O(1) 時間で可能な配列

  # Usage
    - InitializableArray<T> x(n): 型 T の n 個の要素からなる配列 x を構築 [Time O(n)]
    - set(i, a): x[i] に a を代入 [Time O(1)]
    - x[i]: x[i] を返す [Time O(1)]
    - init(a): x のすべての要素に a を代入 [Time O(1)]

  # Description
    init(a) を実現するために領域を (2 * n + 2) * sizeof(size_t) + sizeof(T) だけ追加している．
    上の操作を実現する抽象配列を Z とする．initv は最近行われた init(a) の a の値で，
    init(a) を from と スタック to（スタックサイズ b）を用いたチェインという概念で実現する．
    Z[i] は i 番目がチェインのとき value[i] で，チェインでないとき initv とする．
    i 番目がチェインであるとは，from[i] がスタックに push されており (from[i] < b)，
    かつ，from[i] と to がリンクしていることである（to[from[i]] = i）．

    init(a) はスタックを空にして（b = 0），initv = a とすればよい．
    set(i, a) は i 番目がチェインのときは value[i] = a として，チェインでないときはスタックに
    from[i] を追加して to とリンクしてから value[i] = a とする．
    x[i] も i　番目がチェインであるかどうかで value[i] を返すか initv を返すかを行えばよい．
    これらは，すべて O(1) 時間で実現可能である．

  # Note
    @tmaehara さんの実装を vector にしただけ・・・．TODO としてどっちが高速なのかの実験を行う．
    @kgoto さんのブログに追加領域をより少なくできる論文があると書かれているのでいつか実装する．

  # References
    - [spagetthi source @tmaehara]
      (https://github.com/spaghetti-source/algorithm/blob/master/data_structure/initializable_array.cc)
    - [初期化配列の実装 @kgoto](https://qiita.com/kgoto/items/0251e442292d8ebc1f3d)

  # Verified

*/

#include <bits/stdc++.h> // Replace needed headers for speed up

// -------------8<------- start of library -------8<------------------------
template <class T>
struct InitializableArray {
    T initv;
    size_t n, b;
    std::vector<T> value;
    std::vector<size_t> from, to;

    InitializableArray(int _n) : n(_n), b(0), value(n), from(n), to(n) {}

    bool chain(const size_t i) const { return from[i] < b && to[from[i]] == i; }
    T operator[](const size_t i) const { return chain(i) ? value[i] : initv; }
    void init(const T &a) { initv = a; b = 0; }
    void set(const size_t i, const T &a) {
        if (!chain(i)) { from[i] = b; to[b++] = i; }
        value[i] = a;
    }
};
// -------------8<------- end of library ---------8-------------------------

int main() {
    std::cin.tie(0); std::ios::sync_with_stdio(false);

    constexpr int n = 5;
    InitializableArray<int> x(n);

    for (int i = 0; i < n; ++i) x.set(i, i);
    for (int i = 0; i < n; ++i) std::cout << x[i] << " \n"[i == n -1];

    x.init(2 * n);
    for (int i = 0; i < n; ++i) std::cout << x[i] << " \n"[i == n -1];

    x.set(0, 0);
    x.set(n - 1, n - 1);
    for (int i = 0; i < n; ++i) std::cout << x[i] << " \n"[i == n -1];

    x.init(3 * n);
    for (int i = 0; i < n; ++i) std::cout << x[i] << " \n"[i == n -1];

    return 0;
}
