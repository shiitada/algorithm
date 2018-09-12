/*
  Maximum Bipartite Matching (using Ford-Fulkerson)
  =================================================

  # Problem
    Input: 二部グラフ G = (A; B, E)
    Output: G の最大マッチングのサイズ

    Def. マッチング(Matching)
      G のマッチングとは，辺部分集合 M \subseteq E で M のどの異なる2辺も端点が異なるもの．
      サイズが最大となるマッチングを最大マッチングと呼ぶ

  # Complexity
    Time : O(|V| * (|V| + |E|))
    Space : O(|V| + |E|)

  # Description
    For-Fulkersonのように増加道をDfsで見つけてくる

  # References
    [@tmaehara spagetthi-source/algorithm/graph/bipartite_matching]
    (https://github.com/spaghetti-source/algorithm/blob/master/graph/bipartite_matching.cc)

  # Verified
    [AOJ GRL_7_A Matching - Bipartite Matching]
    (http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A)
*/

#include <iostream>
#include <vector>

using namespace std;

// -------------8<------- start of library -------8<------------------------
class BipariteGraph {
public:
    // Bipartite Graph G = (A; B, E), A = [0, L), B = [L, L + R)
    BipariteGraph(int _L, int _R)
        : L(_L), R(_R), adj(L + R), match_to(L + R, -1), visited(L + R), size_match(0) {}

    void add_edge(const int v1, const int v2) {
        adj[v1].push_back(L + v2);
        adj[L + v2].push_back(v1);
    }

    int MaximumMatching() {
        for (int v = 0; v < L; ++v) {
            fill(visited.begin(), visited.end(), false);
            if (Augment(v)) ++size_match;
        }

        /* もし解が必要ならばコメントアウト */
        // vector<pair<int, int>> matching(size_match);
        // for (int v = 0, idx = 0; v < L; ++v)
        //     if (0 <= match_to[v])
        //         matching[idx++] = {v, match_to[v] - L};

        return size_match;
    }

private:
    const int L, R;
    vector<vector<int>> adj;
    vector<int> match_to;
    vector<bool> visited;
    int size_match;

    bool Augment(const int cur) {
        for (const int dst : adj[cur])
            if (!visited[dst]) {
                visited[dst] = true;
                if (match_to[dst] < 0 || Augment(match_to[dst])) {
                    match_to[cur] = dst; match_to[dst] = cur;
                    return true;
                }
            }
        return false;
    }
};
// -------------8<------- end of library ---------8-------------------------

int main() {
    cin.tie(0); ios::sync_with_stdio(false);

    int L, R, m;
    cin >> L >> R >> m;

    // prtite sets : A = [0, L), B = [0, R)
    BipariteGraph g(L, R);
    for (int i = 0, v[2]; i < m; ++i) {
        cin >> v[0] >> v[1];
        g.add_edge(v[0], v[1]);
    }

    cout << g.MaximumMatching() << endl;

    return 0;
}
