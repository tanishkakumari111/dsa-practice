#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    long long maximumProfit(vector<int>& prices, int k) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;

        vector<long long> flat(k + 1, LLONG_MIN);
        vector<long long> longPos(k + 1, LLONG_MIN);
        vector<long long> shortPos(k + 1, LLONG_MIN);

        flat[0] = 0;

        for (int price : prices) {
            for (int t = k - 1; t >= 0; t--) {
                // Close positions
                if (longPos[t] != LLONG_MIN)
                    flat[t + 1] = max(flat[t + 1], longPos[t] + price);

                if (shortPos[t] != LLONG_MIN)
                    flat[t + 1] = max(flat[t + 1], shortPos[t] - price);

                // Open positions
                if (flat[t] != LLONG_MIN) {
                    longPos[t]  = max(longPos[t],  flat[t] - price);
                    shortPos[t] = max(shortPos[t], flat[t] + price);
                }
            }
        }

        long long ans = 0;
        for (int t = 0; t <= k; t++)
            ans = max(ans, flat[t]);

        return ans;
    }
};
