/*
  Decomposition of strongly connected components (Kosaraju)
  強連結成分分解
  =========================================================

  # Problem
    Input: 有向グラフ G = (V, E)
    Output: G 強連結成分分解

    Def. 強連結(strongly connected)
      G が強連結であるとは，任意の2頂点間の間に有向道が存在すること

    Def. 強連結成分(strongly connected component)
      G の強連結成分とは G の極大で強連結な部分グラフ

  # Complexity (n = |V|, m = |E|)
    Time: O(n + m)
    Memory: O(n + m)

  # Usage
    - Graph g(n): 頂点数 n の有向グラフを構成
    - g.add_edge(u, v): g に弧 (u, v) を追加
    - g.StronglyConnectedComponents(): g の強連結成分分解を行う
    - g.scc[v]: v が属する強連結成分の番号(成分グラフのトポロジカルソート順)

  # Description
    1. G の深さ優先探索を行い post order で各頂点 v の訪れた順番 p(v) を記録する．
       実装では i 番目に訪れた頂点を ord[i] としている．
    2. p の値が大きい頂点 v から G の逆辺(radj)に従って深さ優先探索を行う．
       このとき，v から訪れることができる頂点部分集合が v が属する強連結成分である．

    Def. 強連結成分の成分グラフ(component graph)
      G の強連結成分 S_1, ..., S_k の成分グラフ G' = (V', E') とは，
       ・ V' = {v_1, .., v_k} : S_i に対応する頂点を v_i とする
       ・ (v_i, v_j) \in E'  <=> ある u \in S_i, v \in S_j が存在して (u, v) \in E

    G の成分グラフはDAGであり，scc はトポロジカルソートの順番と対応する．
    解の正当性の証明はアルゴリズムイントロダクションを参照．

  # References
    - [spagetthi-source @tmaehara]
      (https://github.com/spaghetti-source/algorithm/blob/master/graph/strongly_connected_component_kosaraju.cc)
    - [高校数学の美しい物語　強連結成分分解の意味とアルゴリズム](http://mathtrain.jp/kyorenketsu)
    - あり本．pp. 285--287.
    - アルゴリズムイントロダクション. pp. 512-515.

  # Verified
    - [AOJ GRL_3_C Connected Components - Strongly Connected Components]
      (http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C)
*/

#include <iostream>
#include <vector>

// -------------8<------- start of library -------8<------------------------
struct Graph {
    const int n;
    std::vector<std::vector<int>> adj, radj;
    std::vector<int> scc;

    Graph(int _n) : n(_n), adj(n), radj(n), scc(n, false) {}

    void add_edge(int src, int dst) { adj[src].push_back(dst); radj[dst].push_back(src); }

    void Dfs(const int cur, auto &ord) {
        scc[cur] = true;
        for (auto dst : adj[cur])
            if (!scc[dst]) Dfs(dst, ord);
        ord.push_back(cur);
    }
    void RevDfs(const int id, const int cur) {
        scc[cur] = id;
        for (auto dst : radj[cur])
            if (scc[dst] == -1) RevDfs(id, dst);
    }

    void StronglyConnectedComponents() {
        std::vector<int> ord;
        for (int v = 0; v < n; ++v)
            if (!scc[v]) Dfs(v, ord);

        std::fill(scc.begin(), scc.end(), -1);
        for (int i = n - 1, no = 0; 0 <= i; --i)
            if (scc[ord[i]] == -1) RevDfs(no++, ord[i]);
    }
};
// -------------8<------- end of library ---------8-------------------------

int main() {
    std::cin.tie(0); std::ios::sync_with_stdio(false);

    // AOJ GRL_3_C Connected Components - Strongly Connected Components
    int n, m, v[2];
    std::cin >> n >> m;

    Graph g(n);
    for (int i = 0; i < m; ++i) {
        std::cin >> v[0] >> v[1];
        g.add_edge(v[0], v[1]);
    }

    g.StronglyConnectedComponents();

    int q;
    std::cin >> q;
    while (q--) {
        std::cin >> v[0] >> v[1];
        std::cout << (g.scc[v[0]] == g.scc[v[1]]) << '\n';
    }

    return 0;
}
