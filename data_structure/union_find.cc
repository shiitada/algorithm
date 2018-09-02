/*
  Union Find Data Structure
  =========================

  # Description
    - each element label is in [0, N)
    - unite(x, y) : merge sets containing x and y.
    - find(x, y) : return true if x and y are in the same set
    - size(x) : return the size of the set containing x

  # Complexity
    Amortized O(a(n)) for all operations.
    a(n) is the inverse Ackermann function.
    In almost situations a(n) <= 4.

  # References
    - [AtCoder Union-Find](https://www.slideshare.net/chokudai/union-find-49066733)
    - [@tmaehara, spagetthi-source Union Find]
    (https://github.com/spaghetti-source/algorithm/blob/master/data_structure/union_find.cc)

  # Verified

*/

#include <iostream>
#include <vector>

// -------------8<------- start of library -------8<------------------------
struct UnionFind {
    std::vector<int> data;

    UnionFind(int size) : data(size, -1) {}

    bool unite(int x, int y) {
        x = root(x); y = root(y);
        if (x != y) {
            if (data[y] < data[x]) swap(x, y);
            data[x] += data[y]; data[y] = x;
        }
        return x != y;
    }
    bool find(int x, int y) { return root(x) == root(y); }
    int size(int x) { return -data[root(x)]; }
    int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
};
// -------------8<------- end of library ---------8-------------------------


int main() {
    UnionFind uf(5); // data[0, 5)

    uf.unite(1, 2);
    uf.find(1, 2); // true
    uf.find(1, 3); // false
    uf.size(1);    // 2 ({1, 2})

    return 0;
}
