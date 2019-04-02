Tree Isomorphism Problem (Aho, Hopcroft, Ullman)  
木の同型性判定問題  
========================================
[Source Code](tree_isomorphism.cc)

# Problem
**Input**: 木 T, S  
**Output**: TとSが同型であるか  

**Def. グラフ同型（isomorphic）**
T と S が同型であるとは，全単射 f : V(T) -> V(S) が存在して， 任意の u, v \in V(T) に対して，
{u, v} \in E(T) <==> {f(u), f(v)} \in E(S**
が成り立つこと．f を同型写像（isomorphism）と呼ぶ．

**Def. 根付き木の同型**
　根付き木 (T, t) と (S, s) が同型であるとは，同型写像 f : V(T) -> V(S) が存在して，
　かつ，f(t) = s を満たす．

**Def. 順序木の同型**
　順序木 (T, t, <_T) と (S, s, <_S) が同型であるとは，根付き木の同型写像 f : V(T) -> V(S)
　が存在して，v \in V(T) に対して，その子全体が c1 <_T c2 <_T ... <_T c_k のとき，
　f(c_1) <_S f(c_2) <_S ... <_S f(c_k) を満たす．

# Complexity
**Time and Space** : O(n)

# Description
　木，根付き木，順序木の順番に条件が強くなるので，まず順序木の同型性判定から行う．
各頂点に二進列をコードとして割り当てる．各葉に 10 を割り当てて，
頂点 v の子のコードがそれぞれ A_1, A_2, ..., A_t のとき（対応する頂点は線形順序），
v のコードを 1 A_1 A_2 ... A_t 0 と連結する．   
　根付き木では A_1, A_2, ..., A_t を連結する順番を決める必要があるが，
各頂点のコードが二進列であることから自然な順序を定義できて順序木に帰着できる．
ここの実装をどうするかによって，O(n) か O(n log n) となる．  
　木の場合は根付き木に帰着するが，根をどうするかが問題となる．ここで，木の不変量である中心を用いる．
木の頂点 v の離心率とは v から最長の距離で，離心率が最小となる頂点集合が中心である．
どの木も中心のサイズは高々2なので根の選び方を全通り試す．中心は直径の中央値であるが，
直径は幅優先探索を2回すると O(n) で求まる．  
実装方法は2つの木の根から遠いレイヤーごとに行う．上では各頂点に二進列をコードとして割り当てたが，
ここでは自然数を割り当てる．あるレイヤーの2つの木の頂点全体を考える．
ここで，各頂点の子に対しては自然数が割り当てられており，その子全体のコードを昇順に並べた
自然数列が対応付けられる．このとき，それぞれの自然数列を辞書式順序で昇順に並べて，対応する自然数列が
左から何番目にあるかをその頂点のコードとする．  
　ここで，ある頂点の子の自然数の集合を昇順に並べる方法に計数ソートを用いて，
自然数列を並べる方法に基数ソートを用いる．各レイヤーの頂点数を l_1, l_2, ..., l_k とすると，
i番目のレイヤーの自然数列の各要素の総和 l_{i+1} 以下となるので，
計算時間は O(l_1 + l_2 + ... + l_k) = O(n) となる．  
　計数ソートや基数ソートではないソートと用いると O(n log n) となるが導出が良くわからない．

# Note
SPOJ では tmaeharaさんの O(n log n) 時間のアルゴリズムの方が高速（logは定数） orz

# References
- A. V. Aho, J. E. Hopcroft, and J. D. Ullman (1974):
The Design and Analysis of Computer Algorithms.Addison-Wesley.
- [@tmaehara: spagetthi-soucr/algorithm/tree_isomorphism.cc](https://github.com/spaghetti-source/algorithm/blob/master/graph/tree_isomorphism.cc)

# Verified
- [SPOJ 7826 : TREEISO - Tree Isomorphism](https://www.spoj.com/problems/TREEISO/)
