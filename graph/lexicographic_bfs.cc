/*
  Lexicographic Breadth First Search (Rose, Tarjan, Lueker 1976)
  辞書順幅優先探索
  ==============================================================

  # Problem
    Input: Undirected Graph G = (V, E)
    Output: V上の線形順序 (LexBfs)

  # Complexity
    Time and Space: O(|V| + |E|)

  # Usage
    vector<int> LexBfs(vector<vector<int>> G)

  # Description
    G の Lexicographic Bradth First Search(LexBfs) とは BFS の一種である．
    ある頂点を始点としてBFSを行うが，次に訪れる頂点は，未訪問の頂点で，その頂点に隣接している
    訪問済みの頂点らの訪れた順番の辞書式順序が最も小さいものが選ばれる．
    例えば，未訪問の頂点が2つあり，それぞれの隣接している訪問済み頂点の訪れた順番が 1,3,4 と
    1,3,6 のときは前者が次に選ばれる．
    線形時間で実行するために Partition Refinement を実装した．

  # References
    Derek G. Corneil : Lexicographic Breadth First Search -- A Survey.
    International Workshop on Graph-Theoretic Concepts in Computer Science,
    Bad Honnef, Germany, June 21-23, 2004, pp. 1--19.

  # Verified

*/

#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

// ------------8<------- start of library -------8<-------------------------------
std::vector<int> LexBfs(const Graph &g) {
    struct Data {
        Data(int _s) : prev(nullptr), nxt(nullptr), size(_s), size_new(0), item(_s) {}
        Data *prev, *nxt;
        int size, size_new;
        std::vector<int> item;
    };

    const int n = g.size();
    std::vector<int> order(n, -1);
    std::vector<char> visited(n, false); // vector<bool> is slow
    std::vector<std::pair<Data*, int>> ptr(n);
    Data data(n);
    for (int i = 0;  i < n; ++i) {
        ptr[i] = std::make_pair(&data, i);
        data.item[i] = i;
    }

    Data *head = &data;
    int size_order = 0;
    while (size_order < n) {
        // choosing a pivot
        const int pivot = order[size_order++] = head->item[0];
        visited[pivot] = true;
        std::swap(head->item[0], head->item[head->size - 1]);
        std::swap(ptr[head->item[0]].second, ptr[head->item[head->size - 1]].second);
        --(head->size);
        if (head->size == 0) head = head->nxt;

        // selecting vertices to partition
        for (const auto u : g[pivot]) {
            if (visited[u]) continue;

            Data *cur = ptr[u].first;
            if (cur->size == 1) continue;

            const int idx = ptr[u].second;
            std::swap(cur->item[idx], cur->item[cur->size - cur->size_new - 1]);
            std::swap(ptr[u].second, ptr[cur->item[idx]].second);
            ++(cur->size_new);
        }

        // partitioning
        for (const auto u : g[pivot]) {
            if (visited[u]) continue;

            Data *cur = ptr[u].first;
            if (cur->size_new == 0 || cur->size == cur->size_new) {
                cur->size_new = 0;
                continue;
            }

            const int size_new = cur->size_new;
            Data *new_data = new Data(size_new);
            for (int i = 0; i < size_new; ++i) {
                new_data->item[i] = cur->item[cur->size - size_new + i];
                ptr[new_data->item[i]].first = new_data;
                ptr[new_data->item[i]].second = i;
            }

            if (head == cur) head = new_data;

            cur->size -= cur->size_new;
            cur->size_new = 0;
            new_data->prev = cur->prev;
            new_data->nxt = cur;
            if (new_data->prev != nullptr) new_data->prev->nxt = new_data;
            cur->prev = new_data;
        }
    }

    return order;
}
// -------------8<------- end of library -------8<-----------------------------


int main() {
    // Input Undirected Graph G = (V, E)
    // n := |V|, m := |E|
    int n, m, v[2];
    std::cin >> n >> m;

    Graph g(n);
    for (int i = 0; i < m; ++i) {
        std::cin >> v[0] >> v[1];
        for (int j = 0; j <= 1; ++j)
            g[v[j]].push_back(v[1 - j]);
    }

    // Output LBFS ordering of vertices V
    auto ord = LexBfs(g);
    for (int i = 0; i < n; ++i)
        std::cout << ord[i] << " \n"[i == n - 1];

    return 0;
}
