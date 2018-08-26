/*
  Fenwick Tree (Peter M. Fenwick 1994)
  ===============================

  # Algorithm
    Input: n個の変数 v_0, ..., v_{n-1}
    Query:
      1. v_i に w を加える : v_i += w        : O(1) 時間
      2. v_0 + v_1 + ... + v_{i-1} を求める　: O(log n) 時間

  # Usage
    - FenwickTree<T> tree(n) : 型 T でサイズ n の Fenwick Tree を作成 (bit[i] = 0)
    - T tree.sum(r) : bit[0] + bit[1] + ... + bit[r - 1] を
    - T tree.sum(l, r) : bit[l] + bit[l+1] + ... + bit[r - 1] を返す
    - void tree.add(i, a) : bit[i] += a
    - int tree.size() : サイズ n を返す

  # Note
    Binary Indexed Tree とも呼ばれる
    ここでは，1-idx よりも 0-idx でも実装を行っている
    平衡二分探索木やSegment Treeよりも定数倍の意味で高速（bit演算と少ない領域）

  # References
    [保坂和宏，Binary Indexed Treeのはなし（2018年8月26日アクセス）]
    (http://hos.ac/slides/20140319_bit.pdf)

  # Verified
    [AOJ DSL-DSL_2_B ``Range Query'']
    (http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp)
*/

#include <bits/stdc++.h> // Replace needed headers for speed up

// -------------8<------- start of library -------8<------------------------
template <class T>
class FenwickTree {
public:
    FenwickTree(int _n = 0) : n(_n), bit(n + 1, 0) {}

    T sum(int r) const {
        T res = 0;
        for (r = r - 1; r >= 0; r = (r & (r + 1)) - 1) res += bit[r];
        return res;
    }
    T sum(int l, int r) const { return sum(r) - sum(l); }
    void add(int idx, const T &w) { for (; idx < n; idx |= idx + 1) bit[idx] += w; }
    int size() const { return n; }

private:
    const int n;
    std::vector<T> bit;
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
