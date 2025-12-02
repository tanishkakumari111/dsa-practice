#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        const long long MOD = 1000000007;
        unordered_map<long long, long long> cnt;
        for (auto &p : points) {
            long long y = p[1];
            cnt[y]++;
        }

        long long res = 0;
        long long sumPairs = 0;

        for (auto & [y, c] : cnt) {
            if (c >= 2) {
                long long pairs = (c * (c - 1) / 2) % MOD;
                // pairs from previous levels can pair with this level to form trapezoids
                res = (res + pairs * sumPairs) % MOD;
                sumPairs = (sumPairs + pairs) % MOD;
            }
        }

        return (int) res;
    }
};
