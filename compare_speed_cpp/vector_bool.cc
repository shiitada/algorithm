/*
  Is it true that std::vector<bool> is slow?
  ==========================================

  Comparing the execution time in 4 data structures
    1. boost::dynamic_bitset<>
    2. std::vector<bool>
    3. std::vector<char>
    4. std::vector<int>

  My opinion
    small size of a data and only using sequcence iteration -> vector<char>
    otherwise -> vector<bool> or dynamic_bitset (if you can use the boost)

  Result executed this code on my computer.
    - OS : Ubuntu 18.04.1 LTS (Bionic Beaver)
    - Compiler : gcc version 7.3.0
  --------------------------------------------------------------
  n = 100                   sequcence     random
  boost::dynamic_bitset<> :         1,         1 [ms]
        std::vector<bool> :         1,         1 [ms]
        std::vector<char> :         0,         0 [ms]
         std::vector<int> :         0,         0 [ms]

  n = 1000                  sequcence     random
  boost::dynamic_bitset<> :        12,        12 [ms]
        std::vector<bool> :        14,        13 [ms]
        std::vector<char> :         4,        10 [ms]
         std::vector<int> :         5,        12 [ms]

  n = 10000                 sequcence     random
  boost::dynamic_bitset<> :       147,       189 [ms]
        std::vector<bool> :       144,       181 [ms]
        std::vector<char> :        56,       145 [ms]
         std::vector<int> :        57,       157 [ms]

  n = 100000                sequcence     random
  boost::dynamic_bitset<> :      1622,      2218 [ms]
        std::vector<bool> :      1631,      2270 [ms]
        std::vector<char> :       825,      2379 [ms]
         std::vector<int> :       931,      3433 [ms]

  n = 500000                sequcence     random
  boost::dynamic_bitset<> :      8458,     13553 [ms]
        std::vector<bool> :      8302,     13195 [ms]
        std::vector<char> :      3148,     16827 [ms]
         std::vector<int> :      4609,     27012 [ms]

  n = 1000000               sequcence     random
  boost::dynamic_bitset<> :     16623,     28676 [ms]
        std::vector<bool> :     15989,     27766 [ms]
        std::vector<char> :      6918,     31131 [ms]
         std::vector<int> :      6210,     37054 [ms]
  -----------------------------------------------------------------

*/

#include <bits/stdc++.h>
#include <boost/dynamic_bitset.hpp>

void Solve(const bool flag, const int n, auto &d, const auto &idx) {
    constexpr int size_loop = 1000;

    if (flag) { // sequence iteration
        for (int i = 0; i < size_loop; ++i) {
            for (int j = 0; j < n; ++j) d[j] = ((i + j) % 2 == 0);
            for (int j = 0; j < n; ++j) d[j] = !d[j];
            for (int j = 0; j < n; ++j) if (!d[j]) d[j] = true;
            for (int j = n - 1; 0 <= j; --j) d[j] = ((i + j) % 5 == 0);
            for (int j = 0; j < n; ++j) if (d[j]) d[j] = false;
            for (int j = n - 1; 0 <= j; --j) d[j] = !d[j];
        }
    }
    else { // random access iteration
        for (int i = 0; i < size_loop; ++i) {
            for (const int j : idx) d[j] = ((i + j) % 2 == 0);
            for (const int j : idx) d[j] = !d[j];
            for (const int j : idx) if (!d[j]) d[j] = true;
            for (const int j : idx) d[j] = ((i + j) % 5 == 0);
            for (const int j : idx) if (d[j]) d[j] = false;
        }
    }
}

int main() {

    std::vector<std::string> name = {
        "boost::dynamic_bitset<>",
        "      std::vector<bool>",
        "      std::vector<char>",
        "       std::vector<int>",
    };
    std::vector<std::function<void(bool, int, std::vector<int>)>> func = {
        [](const bool flag, const int n, const std::vector<int> &idx)
        { boost::dynamic_bitset<> d(n); Solve(flag, n, d, idx); },

        [](const bool flag, const int n, const std::vector<int> &idx)
        { std::vector<bool> d(n); Solve(flag, n, d, idx); },

        [](const bool flag, const int n, const std::vector<int> &idx)
        { std::vector<char> d(n); Solve(flag, n, d, idx); },

        [](const bool flag, const int n, const std::vector<int> &idx)
        { std::vector<int> d(n); Solve(flag, n, d, idx); },
    };

    const int size_algo = name.size(), size_loop = 5;
    const std::vector<int> size_data = {100, 1000, 10000, 100000, 500000, 1000000};

    using namespace std::chrono;

    for (const int n : size_data) {
        std::cout << "n = " << n << std::string(21 - (int)log10(n), ' ')
                  << "sequcence     random" << std::endl;

        // make random access iterator
        std::vector<int> idx(n); std::iota(idx.begin(), idx.end(), 0);
        std::shuffle(idx.begin(), idx.end(), std::mt19937(0));

        for (int i = 0; i < size_algo; ++i) {
            auto sum_time1 = 0, sum_time2 = 0;

            // measure average execution time
            for (int j = 0; j < size_loop; ++j) {
                // count time : sequcence access
                auto start = high_resolution_clock::now();
                func[i](true, n, idx);
                auto end = high_resolution_clock::now();
                sum_time1 += duration_cast<milliseconds>(end - start).count();

                // count time : random access
                start = high_resolution_clock::now();
                func[i](false, n, idx);
                end = high_resolution_clock::now();
                sum_time2 += duration_cast<milliseconds>(end - start).count();
            }

            // Output
            std::cout << name[i] << " : "
                      << std::setw(9) << std::right << sum_time1 / size_loop << ", "
                      << std::setw(9) << std::right << sum_time2 / size_loop << " [ms]\n";
        }
        std::cout << std::endl;
    }

    return 0;
}
