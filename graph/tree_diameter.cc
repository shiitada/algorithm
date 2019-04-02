#include <iostream>
#include <vector>

// -------------8<------- start of library -------8<------------------------
template<class W>
struct Tree {
    int n;
    std::vector<std::vector<std::pair<int, W>>> adj;

    explicit Tree(int _n) : n(_n), adj(_n) {}
    void add_edge(const int v1, const int v2, const W w) {
        adj[v1].emplace_back(std::make_pair(v2, w));
        adj[v2].emplace_back(std::make_pair(v1, w));
    }

    std::pair<int, W> Dfs(const int prev, const int cur) {
        std::pair<int, W> res(cur, 0);
        for (const auto &e : adj[cur]) {
            if (prev == e.first) continue;
            auto nxt = Dfs(cur, e.first); nxt.second += e.second;
            if (res.second < nxt.second) res = nxt;
        }
        return res;
    }

    std::pair<int, int> farthest_pair;
    W Diameter() {
        const auto v1 = Dfs(-1, 0), v2 = Dfs(-1, v1.first);
        farthest_pair = std::make_pair(v1.first, v2.first);
        return v2.second;
    }
};
// -------------8<------- end of library ---------8-------------------------


int main() {
    std::cin.tie(0); std::ios::sync_with_stdio(false);

    // AOJ GRL_5_A Tree - Diameter of a Tree
    int n;
    std::cin >> n;

    Tree<int> tree(n);
    for (int i = 0, s, t, w; i < n - 1; ++i) {
        std::cin >> s >> t >> w;
        tree.add_edge(s, t, w);
    }

    std::cout << tree.Diameter() << std::endl;

    return 0;
}
