#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// @require algorithm/other/counting_sort.cc

// -------------8<------- start of library -------8<------------------------
struct Tree {
    const int n;
    std::vector<std::vector<int>> adj;

    explicit Tree(int _n) : n(_n), adj(_n) {}
    void add_edge(const int v1, const int v2) {
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }

    std::vector<int> centers() {
        std::vector<int> prev(n);
        int u = 0;
        for (int i = 0; i < 2; ++i) { // double sweap
            prev.assign(n, -1);
            std::queue<int> que;
            que.push(prev[u] = u);
            while (!que.empty()) {
                u = que.front(); que.pop();
                for (auto v : adj[u]) {
                    if (prev[v] == -1) {
                        prev[v] = u;
                        que.push(v);
                    }
                }
            }
        }

        std::vector<int> path = {u};
        while (prev[u] != u) path.push_back(u = prev[u]);

        if (path.size() % 2 == 1) return {path[path.size() / 2]};
        else return {path[path.size() / 2 - 1], path[path.size() / 2]};
    }

    std::vector<std::vector<int>> layer;
    std::vector<int> prev;
    int levelize(const int root) { // split vertices into levels
        layer = {{root}};
        prev.assign(n, -1); prev[root] = n;

        while (true) {
            std::vector<int> next;
            for (int u : layer.back()) {
                for (int v : adj[u])
                    if (prev[v] == -1) {
                        prev[v] = u;
                        next.push_back(v);
                    }
            }
            if (next.empty()) break;
            layer.emplace_back(next);
        }

        return layer.size();
    }
};

void RadixSort(std::vector<std::pair<bool, int>> &idx, const int len,
               const int ub, const std::vector<std::vector<int>> &lcS,
               const std::vector<std::vector<int>> &lcT) {
    const int n = idx.size();

    // counting sort
    std::vector<int> cnt(ub + 1);
    auto tmp = idx;
    for (int i = len - 1; 0 <= i; --i) {
        cnt.assign(ub + 1, 0);
        for (const auto &it : idx) {
            auto &code = (it.first ? lcS[it.second] : lcT[it.second]);
            if ((int)code.size() <= i) ++cnt[0];
            else ++cnt[code[i]];
        }
        for (int j = 1; j <= ub; ++j) cnt[j] += cnt[j - 1];

        for (int j = n - 1; 0 <= j; --j) {
            auto &code = (idx[j].first ? lcS[idx[j].second] : lcT[idx[j].second]);

            if ((int)code.size() <= i) {
                tmp[cnt[0] - 1] = idx[j];
                --cnt[0];
            }
            else {
                tmp[cnt[code[i]] - 1] = idx[j];
                --cnt[code[i]];
            }
        }
        for (int j = 0; j < n; ++j) idx[j] = tmp[j];
    }
}

bool Isomorphic(Tree S, const int s, Tree T, const int t) {
    if (S.levelize(s) != T.levelize(t)) return false;

    std::vector<std::vector<int>> longcodeS(S.n + 1), longcodeT(T.n + 1);
    std::vector<int> codeS(S.n), codeT(T.n);

    int max_len_code = 0, max_element = 0;

    for (int h = S.layer.size() - 1; 0 <= h; --h) {
        for (int v : S.layer[h])
            CountingSort(longcodeS[v].begin(), longcodeS[v].end());
        for (int v : T.layer[h])
            CountingSort(longcodeT[v].begin(), longcodeT[v].end());

        std::vector<std::pair<bool, int>> idx;
        for (int v : S.layer[h]) idx.push_back({true, v});
        for (int v : T.layer[h]) idx.push_back({false, v});

        // Radix Sort
        RadixSort(idx, max_len_code, max_element, longcodeS, longcodeT);

        int id = 1;
        max_len_code = 0;
        for (size_t i = 0; i < idx.size(); ++i) {
            if (i != 0) {
                auto &lc1 = (idx[i - 1].first ? longcodeS[idx[i - 1].second]
                             : longcodeT[idx[i - 1].second]);
                auto &lc2 = (idx[i].first ? longcodeS[idx[i].second]
                             : longcodeT[idx[i].second]);
                if (lc1 != lc2) ++id;
            }

            if (idx[i].first) {
                codeS[idx[i].second] = id;
                longcodeS[S.prev[idx[i].second]].push_back(id);
                max_len_code = std::max(max_len_code,
                    (int)longcodeS[S.prev[idx[i].second]].size());
            }
            else {
                codeT[idx[i].second] = id;
                longcodeT[T.prev[idx[i].second]].push_back(id);
                max_len_code = std::max(max_len_code,
                                        (int)longcodeS[T.prev[idx[i].second]].size());
            }
        }
        max_element = id;
    }

    return codeS[s] == codeT[t];
}

bool Isomorphic(Tree S, Tree T) {
    // Suppose that S and T are trees (connected and edge size == n - 1).
    if (S.n != T.n) return false;
    if (S.n <= 2) return true;

    auto s = S.centers(), t = T.centers();
    if (s.size() != t.size()) return false;
    if (Isomorphic(S, s[0], T, t[0])) return true;
    return s.size() == 2 &&  Isomorphic(S, s[1], T, t[0]);
}

// -------------8<------- end of library ---------8-------------------------

int main() {
    int n_case;
    std::cin >> n_case;
    for (int i_case = 0; i_case < n_case; ++i_case) {
        int n, v[2];

        std::cin >> n;
        Tree S(n), T(n);
        for (int i = 0; i < n - 1; ++i) {
            std::cin >> v[0] >> v[1];
            S.add_edge(v[0] - 1, v[1] - 1);
        }
        for (int i = 0; i < n - 1; ++i) {
            std::cin >> v[0] >> v[1];
            T.add_edge(v[0] - 1, v[1] - 1);
        }

        if (Isomorphic(S, T)) std::cout << "YES\n";
        else std::cout << "NO\n";
    }

    return 0;
}
