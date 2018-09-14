/*
  Is it true that std::vector<bool> is slow?
  ==========================================
  * Assumed usage is only like a flag (access, assignment, negation)

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
  n = 1000                  sequcence     random
  boost::dynamic_bitset<> :         1,         1 [ms]
        std::vector<bool> :         1,         0 [ms]
        std::vector<char> :         0,         0 [ms]
         std::vector<int> :         0,         0 [ms]

  n = 10000                 sequcence     random
  boost::dynamic_bitset<> :        11,        14 [ms]
        std::vector<bool> :        10,        13 [ms]
        std::vector<char> :         4,        10 [ms]
         std::vector<int> :         4,        11 [ms]

  n = 100000                sequcence     random
  boost::dynamic_bitset<> :       130,       162 [ms]
        std::vector<bool> :       123,       160 [ms]
        std::vector<char> :        49,       158 [ms]
         std::vector<int> :        53,       197 [ms]

  n = 1000000               sequcence     random
  boost::dynamic_bitset<> :      1373,      1898 [ms]
        std::vector<bool> :      1311,      1913 [ms]
        std::vector<char> :       518,      2318 [ms]
         std::vector<int> :       597,      3144 [ms]

  n = 5000000               sequcence     random
  boost::dynamic_bitset<> :      6659,     12744 [ms]
        std::vector<bool> :      6586,     12707 [ms]
        std::vector<char> :      2750,     17679 [ms]
         std::vector<int> :      3219,     37739 [ms]

  n = 10000000              sequcence     random
  boost::dynamic_bitset<> :     13317,     28555 [ms]
        std::vector<bool> :     13491,     29274 [ms]
        std::vector<char> :      5721,     64872 [ms]
         std::vector<int> :      6604,     88075 [ms]
  -----------------------------------------------------------------

*/

#include <bits/stdc++.h>
#include <boost/dynamic_bitset.hpp>

void Solve(const bool flag, const int n, auto &d, const auto &idx) {
    constexpr int size_loop = 100;

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

    // parameter
    const int size_algo = name.size(), size_loop = 20;
    const std::vector<int> size_data = {1000, 10000, 100000, 1000000,
                                        5000000, 10000000};

    using namespace std::chrono;

    for (const int n : size_data) {
        std::cout << "n = " << n << std::string(21 - (int)log10(n), ' ')
                  << "sequcence     random" << std::endl;

        // make random access iterator
        std::vector<int> idx(n); std::iota(idx.begin(), idx.end(), 0);

        // measure average execution time
        std::vector<milliseconds> sum_time1(size_algo), sum_time2(size_algo);
        for (int i = 0; i < size_loop; ++i) {
            std::shuffle(idx.begin(), idx.end(), std::mt19937(0));

            for (int j = 0; j < size_algo; ++j) {
                // count time : sequcence access
                auto start = high_resolution_clock::now();
                func[j](true, n, idx);
                auto end = high_resolution_clock::now();
                sum_time1[j] += duration_cast<milliseconds>(end - start);

                // count time : random access
                start = high_resolution_clock::now();
                func[j](false, n, idx);
                end = high_resolution_clock::now();
                sum_time2[j] += duration_cast<milliseconds>(end - start);
            }
        }

        // Output average execution times
        for (int i = 0; i < size_algo; ++i) {
            std::cout << name[i] << " : " << std::setw(9) << std::right
                      << sum_time1[i].count() / size_loop << ", " << std::setw(9)
                      << std::right << sum_time2[i].count() / size_loop << " [ms]\n";
        }
        std::cout << std::endl;
    }

    return 0;
}
