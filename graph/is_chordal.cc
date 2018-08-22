#include <iostream>
#include <vector>

using namespace std;

using Graph = vector<vector<int>>;


/* 👇 Please paste LexBfs library (lexicographic_bfs.cc) 👇 */


// --------------8<------- start of library -------8<--------------------
bool IsChordal(const Graph &g) {
    const int n = g.size();
    vector<int> idx(n), adj(n, -1), order = LexBfs(g);

    for (int i = 0; i < n; ++i) idx[order[i]] = i;

    for (const int v : order) {
        int p = -1, size = 0;

        for (const int u : g[v]) {
            if (idx[u] < idx[v]) {
                adj[u] = v;
                ++size;
                p = max(p, idx[u]);
            }
        }
        for (const int u : g[order[p]])
            if (adj[u] == v) --size;

        if (p != -1 && size != 1) return false;
    }

    return true;
}
// ----------------8<------- end of library -------8<--------------------


int main() {
    cin.tie(0); ios::sync_with_stdio(false);

    // Input Undirected Graph G = (V, E)
    // n := |V|, m := |E|
    int n, m, v[2];
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        cin >> v[0] >> v[1];
        for (int j = 0; j <= 1; ++j)
            g[v[j]].push_back(v[1 - j]);
    }

    // Output LBFS ordering of vertices V
    cout << (IsChordal(g) ? "Yes " : "No ") << "Chordal Graph\n";

    return 0;
}
