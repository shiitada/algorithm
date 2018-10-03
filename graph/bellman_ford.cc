/*
  Single Source Shortest Path Problem (Bellman Ford)
  単一始点全終点最短路問題（ベルマン・フォード法）
  ===================================================

  # Problem
    Input: 有向グラフ G = (V, E), 辺重み w : E -> R, 始点 s
    Output: s から各頂点 v への最短距離 d[v]

  # Complexity (n = |V|, m = |E|)
    Time: O(n * m)
    Memory: O(n + m)

  # Usage
    - Graph<T> g(n, s): 辺重みの型T，頂点数 n, 始点 s のグラフを構築．
                        2点間最短距離で終点 t が決まっている場合は g(n, s, t) とする
    - g.add_edge(u, v, w): 重み w の弧 (u, v) を追加
    - g.BellmanFord(): ベルマン・フォード法で最短距離を求める
    - g.ShortestDistance(t): s から t への最短距離を返す. g.INF と等しい場合は最短距離は存在しない
    - g.IsNegativeCycle(): s から到達可能な負閉路が存在するとき true を返す

    - g.CheckNegativeCycle(): g に負閉路が存在するか判定する（d は最短距離とは限らない値となる）

  # Note
    - s から到達可能な負閉路の検出ができる (∵ d[s] = 0 として初期化)
     （d[v] = min_{(u, v)} d[u] を各ステップ毎に計算．n回目に更新されたら負閉路が存在する）
    - 負閉路の検出を行いたい場合は各頂点 v に対して d[v] = 0 としてベルマン・フォード法を実行する
      そのとき，d[v] は最短距離を表していないので注意

  # References
    - あり本 pp. 95--96

  # Verified
    - [AOJ Shortest Path - Single Source Shortest Path (Negative Edges)]
      (http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B )
*/

#include <iostream>
#include <vector>
#include <limits>

// -------------8<------- start of library -------8<------------------------
template<class T>
struct Graph {
    struct Edge {
        int dst; T w;
        Edge() {};
        Edge(int _d, T _w) : dst(_d), w(_w) {}
    };

    const int n, s, INF;
    bool is_neg_cycle;
    std::vector<std::vector<Edge>> adj;
    std::vector<T> d;

    Graph(int _n, int _s)
        : n(_n), s(_s), INF(std::numeric_limits<T>::max()),
          is_neg_cycle(false), adj(n), d(n, INF) { }

    void add_edge(int u, int v, T w) { adj[u].emplace_back(Edge(v, w)); }
    T ShortestDistance(const int t) const { return d[t]; }
    bool IsNegativeCycleFromS() const { return is_neg_cycle; }

    bool CheckNegativeCycle() {
        std::fill(d.begin(), d.end(), 0);
        BellmanFord();
        return IsNegativeCycleFromS();
    }

    void BellmanFord() {
        d[s] = 0;
        for (int i = 0; ; ++i) {
            bool update = false;
            for (int v = 0; v < n; ++v)
                for (const auto &e : adj[v])
                    if (d[v] < INF && d[v] + e.w < d[e.dst]) {
                        d[e.dst] = d[v] + e.w;
                        update = true;
                    }
            if (!update) break;
            if (i == n - 1) { is_neg_cycle = true; break; }
        }
    }
};
// -------------8<------- end of library ---------8-------------------------

int main() {
    std::cin.tie(0); std::ios::sync_with_stdio(false);

    // AOJ GPL_1_B: Shortest Path - Single Shortest Path (Negative Edges)
    int n, m, r, s, t, d;
    std::cin >> n >> m >> r;

    Graph<int> g(n, r);
    for (int i = 0; i < m; ++i) {
        std::cin >> s >> t >> d;
        g.add_edge(s, t, d);
    }

    g.BellmanFord();
    if (g.IsNegativeCycleFromS())
        std::cout << "NEGATIVE CYCLE\n";
    else {
        for (int v = 0; v < n; ++v) {
            int dist = g.ShortestDistance(v);
            if (dist == g.INF) std::cout << "INF\n";
            else std::cout << dist << '\n';
        }
    }

    return 0;
}
