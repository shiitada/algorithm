/*
  Counting Sort (stable)
  ======================

  # Problem
    Input: (v_1, v_2, ..., v_n) (0 <= v_i <= k)
    Output: v_i1 <= v_i2 <= ... <= v_it

  # Complexity
    Time : O(n + k)
    Space : O(n + k)

  # References
    T.コルメン，C.ライザーソン，R.リベスト，C.シュタイン（浅野哲夫・岩野和生・梅尾博司・山下雅史・和田幸一 訳）：『アルゴリズムイントロダクション 第3版 総合版：世界標準MIT教科書』．近代工学社，東京，2013．

  # Verified
    [AOJ ALDS1_6_A Sort2 - Counting Sort]
    (http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_6_A)
*/

#include <iostream>
#include <vector>
#include <algorithm>

// -------------8<------- start of library -------8<------------------------
template<class RandomIt>
constexpr void CountingSort(RandomIt first, RandomIt last) {
    const std::size_t size = distance(first, last);
    if (size == 0) return ;

    const auto k = *max_element(first, last);
    std::vector<int> cnt(k + 1);
    for (auto it = first; it != last; ++it) ++cnt[*it];
    for (int i = 1; i <= k; ++i) cnt[i] += cnt[i - 1];

    // the reverse iteration keeps stability
    using vt = typename std::iterator_traits<RandomIt>::value_type;
    std::vector<vt> tmp(size);
    std::reverse_iterator<RandomIt> fst(last);
    std::reverse_iterator<RandomIt> lst(first);
    std::for_each(fst, lst, [&](auto x) {
            tmp[cnt[x] - 1] = x;
            --cnt[x];
    });

    int idx = 0;
    for (auto it = first; it != last; ++it) *it = tmp[idx++];
}
// -------------8<------- end of library ---------8-------------------------

int main() {
    std::cin.tie(0); std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> v(n);
    for (auto &x : v) std::cin >> x;

    CountingSort(v.begin(), v.end());

    for (int i = 0; i < n; ++i)
        std::cout << v[i] << (i == n - 1 ? '\n' : ' ');

    return 0;
}
