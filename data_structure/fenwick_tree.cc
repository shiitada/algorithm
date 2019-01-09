/*
  Fenwick Tree (Peter M. Fenwick 1994)
  フェニック木
  ====================================

  # Problem
    Input: n個の変数 v_0, ..., v_{n-1}
    Query:
      1. v_i に w を加える : v_i += w        : O(1) 時間
      2. v_0 + v_1 + ... + v_{i-1} を求める　: O(log n) 時間

  # Usage
    - FenwickTree<T> tree: 型 T の空の Fenwick Tree を作成（）
    - FenwickTree<T> tree(n): 型 T でサイズ n の Fenwick Tree を作成 (bit[i] = 0)

    - tree.resize(n): tree のサイズを n に変更して，全ての要素を 0 に初期化
    - tree.init(T w): tree の要素を全て w で初期化
    - tree.init(T w, n): tree のサイズを n に変更して，要素を全て w で初期化
    - tree.init(vector<int> w): tree のサイズを w のサイズに変更して，w の要素で初期化

    - T tree.sum(r) : bit[0] + bit[1] + ... + bit[r - 1] を
    - T tree.sum(l, r) : bit[l] + bit[l+1] + ... + bit[r - 1] を返す
    - void tree.add(i, a) : bit[i] += a
    - int tree.size() : サイズ n を返す

  # Note
    Binary Indexed Tree とも呼ばれる
    ここでは 0-idx で実装を行っている
    平衡二分探索木やSegment Treeよりも定数倍の意味で高速（bit演算と少ない領域）

  # References
    [保坂和宏，Binary Indexed Treeのはなし（2018年8月26日アクセス）]
    (http://hos.ac/slides/20140319_bit.pdf )

  # Verified
    [AOJ DSL-DSL_2_B ``Range Query'']
    (http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp )
*/

#include <iostream>
#include <vector>

// -------------8<------- start of library -------8<------------------------
template <class T>
struct FenwickTree {
    size_t n;
    std::vector<T> bit;

    FenwickTree() : n(0) {}
    FenwickTree(int _n) : n(_n), bit(n, 0) {}

    void resize(const int _n) { n = _n; bit.resize(n, 0); }
    void init(const T &w, size_t _n = 0) {
        if (_n != 0) { n = _n; resize(_n); }
        for (size_t i = 0; i < n; ++i) bit[i] = w;
        setup();
    }
    void init(const std::vector<T> &w) {
        if (w.size() != n) resize(w.size());
        for (size_t i = 0; i < n; ++i) bit[i] = w[i];
        setup();
    }
    void setup() { for (size_t i = 0; i < n; ++i) bit[i | (i + 1)] += bit[i]; }

    T sum(int r) const {
        T res = 0;
        for (r = r - 1; r >= 0; r = (r & (r + 1)) - 1) res += bit[r];
        return res;
    }
    T sum(const int l, const int r) const { return sum(r) - sum(l); }
    void add(size_t idx, const T &w) { for (; idx < n; idx |= idx + 1) bit[idx] += w; }
    int size() const { return n; }
};
// -------------8<------- end of library ---------8-------------------------

int main() {
    std::cin.tie(0); std::ios::sync_with_stdio(false);

    int n, q, com, x, y;

    std::cin >> n >> q;
    FenwickTree<int> tree(n);
    while (q--) {
        std::cin >> com >> x >> y;
        if (com == 0) // add : v[x - 1] += y
            tree.add(x - 1, y);
        else if (com == 1) // get prefix : v[x - 1] + ... + v[y - 1]
            std::cout << tree.sum(x - 1, y) << '\n';
    }

    return 0;
}
