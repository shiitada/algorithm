/*
  Algorithm Name (Author)
  =======================

  # Problem
    Input:
    Output:

  # Complexity

  # Usage

  # Description

  # Note

  # References

  # Verified

*/

#include <bits/stdc++.h> // Replace needed headers for speed up

using namespace std;

// -------------8<------- start of library -------8<------------------------
class Tree {
public:
    const int root = 0;
    int n;
    vector<vector<int>> adj;
    Tree(int n = 0) : n(n), adj(n), s1(n, 0), s2(n, 0), s3(n, 0) {}
    void AddEdge(int v1, int v2) {
        adj[v1].emplace_back(v2);
        adj[v2].emplace_back(v1);
    }
    void AddArc(int src, int dst) {
        adj[src].emplace_back(dst);
    }

    // min(s1(root), s2(root))
    int MinimumDominatingSet();
    int Naive();
private:
    vector<int> s1; // T(v)の支配集合で，vを持たないものの最小要素数
    vector<int> s2; // T(v)の支配集合で，vを持つものの最小要素数
    vector<int> s3; // T(v)の頂点部分集合で，T(v)-vの支配集合となるものの最小要素数

    void Dfs(int p, int v);
};

int Tree::Naive() {
    int res = n * n;
    for (int s = 0; s < 1 << n; ++s) {
        bool is_d = true;
        for (int v = 0; v < n; ++v) {
            if (s >> v & 1)
                continue;
            bool flag = false;
            for (auto u : adj[v]) {
                if (s >> u & 1) {
                    flag = true;
                    break;
                }
            }

            if (!flag) {
                is_d = false;
                break;
            }
        }
        if (is_d)
            res = min(res, __builtin_popcount(s));
    }

    return res;
}

void Tree::Dfs(int p, int v) {
    for (auto u : adj[v])
        if (p != u)
            Dfs(v, u);

    bool is_leaf = adj[v].size() == 1;

    int sum_s = 0;
    for (auto u : adj[v])
        if (p != u) {
            sum_s += min(s1[u], s2[u]);
            s2[v] += s3[u];
            s3[v] += s3[u];
        }

    ++s2[v];

    s1[v] = n * n;
    int sum_s3 = 0;
    for (auto u : adj[v])
        if (p != u) {
            sum_s3 += s3[u];
            s1[v] = min(s1[v], s2[u] + sum_s - min(s1[u], s2[u]));
        }

    if (sum_s > 1 + sum_s3) {
        //cout << v << " Error\n";
    }
    //s3[v] = sum_s;
    //s3[v] = 1 + sum_s3;
    s3[v] = is_leaf ? 0 : min(sum_s, 1 + sum_s3);
}

int Tree::MinimumDominatingSet() {
    Dfs(-1, root);

    for (int v = 0; v < n; ++v)
        cout << "v(" << v << ") = " << min(s1[v], s2[v])
             << ", " << s1[v] << ", " << s2[v] << ", " << s3[v] << endl;
    return min(s1[root], s2[root]);
}

// -------------8<------- end of library ---------8-------------------------

int main() {
    cin.tie(0); ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    Tree tree(n);
    for (int i = 0, v[2]; i < n - 1; ++i) {
        std::cin >> v[0] >> v[1];
        tree.add_edge(v[0], v[1]);
    }

    std::cout << tree.MinimumDominatingSet() << std::endl;

    return 0;
}
