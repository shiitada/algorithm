C++ implementations of algorithms
===========================================

# 1. Template
- [Template for competitive programming](template/template.cc)
- [Simple template](template/short_template.cc)
- [Template for algorithm](template/algorithm_template.cc)
- [Template for marathon](template/marathon_template.cc)


# 2. Graph
- [Bipartite maximum matching](graph/bipartite_maximum_matching.cc)
- [Lexicographic breadth first search](graph/lexicographic_bfs.cc)
- [Lowest common ancestor by doubling](graph/lca_doubling.cc)
- [Diameter of a tree](graph/tree_diameter.cc)

## Recognition Problem
- [Tree isomorphism](graph/tree_isomorphism.cc)
- [Recognition of chordal graph](graph/is_chordal.cc)

## Shortest Paths Problem
### Single Source Shortest Paths Problem
- [Dijkstra's algorithm: only distance](graph/dijkstra.cc)
- [Dijkstra's algorithm with heap: only distance](graph/dijkstra_heap.cc)
- [Dijkstra's algorithm with heap: distance and path](graph/dijkstra_heap_sol.cc)
- [Bellman-Ford algorithm: only distance and check for negative cycles](graph/bellman_ford.cc)
- [0-1 BFS algorithm in a binary weighted digraph](graph/01bfs.cc)

### All Pairs Shortest Paths Problem
- [Floyd-Warshall algorithm: only distance](graph/floyd_warshall.cc)

## Connected Components
- [Strongly connected components by kosaraju](graph/strongly_connected_component_kosaraju.cc)
- [2-edge connected components (enumerating all bridges) by Hopcroft and Tarjan](graph/bridge.cc)
- [2-vertex connected components (enumerating all articulation points)](graph/articulation_point.cc)


# 3. Data Structure
- [Fenwick tree (Binary Indexed Tree)](data_structure/fenwick_tree.cc)
- [Union find](data_structure/union_find.cc)


# 4. Number Theory
- [Basic Modular arithmetics](number_theory/modular_arithmetics.cc)
- [Binomial coefficient modulo prime (memorization)](number_theory/choose_mod_memo.cc)
- [Binomial coefficient modulo prime (naive method)](number_theory/choose_mod.cc)
- [GCD (greatest common divisor) and LCM (least common multiple)](number_theory/gcd_lcm.cc)
- [Generate primes at compile time](number_theory/primes_const.cc)
- [Extended Euclid's Algorithm](number_theory/extgcd.cc)
- [Prime factorization - Trial division](number_theory/prime_fact.cc)


# 5. Other
- [Counting sort](other/counting_sort.cc)
- [0-1 Knapsack problem (branch and bound method)](other/01knapsack_problem_branch_and_bound.cc)

## Pseudorandom Number Generator
- [XorShift128 plus by Blackman and Vigna](other/xor_shift128_plus.cc)


# 6. Comparing speed in C++
- [Is it true that std::vector\<bool\> is slow? (only flag usage)](compare_speed_cpp/vector_bool.cc)
