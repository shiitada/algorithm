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
- [Prüfer sequence](graph/prufer_sequence.cc)
- [Maximum independent set problem (using branch and reduce): O*(1.4423) time](graph/maximum_independent_set_1.4423.cc)

## Recognition Problem
- [Recognition of bipartite graph](graph/is_bipartite.cc)
- [Recognition of chordal graph](graph/is_chordal.cc)
- [Recognition of cactus](graph/is_cactus.cc)
- [Eulerian graph by Hierholzer](graph/hierholzer_undirected.cc)
- [Eulerian digraph by Hierholzer](graph/hierholzer_directed.cc)

## Graph Isomorphism Problem
- [Tree isomorphism](graph/tree_isomorphism.cc)

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
- [Strongly connected components by Kosaraju](graph/strongly_connected_component_kosaraju.cc)
- [2-edge connected components (enumerating all bridges) by Hopcroft and Tarjan](graph/bridge.cc)
- [2-vertex connected components (enumerating all articulation points)](graph/articulation_point.cc)

## Tree Problems
- [Lowest common ancestor by doubling](graph/lca_doubling.cc)
- [Lowest common ancestor by euler tour](graph/lca_euler_tour.cc)
- [Diameter of a tree](graph/tree_diameter.cc)

## Maximum Flow Problem
- [Ford-Fulkerson algorithm](graph/maximum_flow_ford_fulkerson.cc)
- [Dinic's algorithm](graph/maximum_flow_dinic.cc)

## Random Graph Generator
- [Erdos-Renyi random graph](graph/erdos_renyi.cc)

### Uniform Spanning Tree
- [Aldous's algorithm](graph/uniform_spanning_tree_aldous.cc)
- [Wilson's algorithm](graph/uniform_spanning_tree_wilson.cc)

### Random Labelled Tree
- [Aldous's algorithm](graph/random_labelled_tree_aldous.cc)
- [Prüfer sequence](graph/random_labelled_tree_prufer_sequence.cc)
- [Wilson's algorithm](graph/random_labelled_tree_wilson.cc)

# 3. Data Structure
- [Fenwick tree (add a single element / accumulate a prefix)](data_structure/fenwick_tree_add_element_accumulate_prefix.cc)
- [Segment tree (update a single element / accumulate an interval)](data_structure/segment_tree_update_element_accumulate_interval.cc)
- [Union find](data_structure/union_find.cc)
- [Initializable array by Bentley](data_structure/initializable_array_bentley.cc)

## Query Problems Using Data Structure
- [Range Sum Query Problem](data_structure/range_sum_query.cc)


# 4. Number Theory
- [Basic Modular arithmetics](number_theory/modular_arithmetics.cc)
- [Binomial coefficient modulo prime (memorization)](number_theory/choose_mod_memo.cc)
- [Binomial coefficient modulo prime (naive method)](number_theory/choose_mod.cc)
- [GCD (greatest common divisor) and LCM (least common multiple)](number_theory/gcd_lcm.cc)
- [Generate primes at compile time](number_theory/primes_const.cc)
- [Extended Euclid's Algorithm](number_theory/extgcd.cc)
- [Prime factorization - Trial division](number_theory/prime_fact.cc)


# 5. Numerical Analysis
- [Gaussian elimination with pivoting](numerical_analysis/gaussian_elimination_with_pivoting.cc)


# 6. Approximation Algorithms
- [Vertex cover problem (using maximal matching): 2-approximation algorithm](approximation_algorithm/vertex_cover_by_maximal_matching_2apx.cc)

# 7. Other
- [Counting sort](other/counting_sort.cc)
- [0-1 Knapsack problem (branch and bound method)](other/01knapsack_problem_branch_and_bound.cc)
- [2-satisfiability problem](other/two_sat.cc)

## Pseudorandom Number Generator
- [XorShift128 plus by Blackman and Vigna](other/xor_shift128_plus.cc)


# 8. Comparing speed in C++
- [Is it true that std::vector\<bool\> is slow? (only flag usage)](compare_speed_cpp/vector_bool.cc)

# 9. 2D Geometry
- [2d geometry](geometry/geometry_basic.cc) (this is not arranged. Let's use CGAL)


# TODO Lists
+ Strongly connected components by Tarjan
+ Max cut prolbme on planar graph by F. Hadlock (1975)
+ The Random Walk Construction of Uniform Spanning Trees and Uniform Labelled Trees

