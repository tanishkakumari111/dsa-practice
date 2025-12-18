class Solution {
public:
    long long maximumProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();

        // Base profit
        long long baseProfit = 0;
        for (int i = 0; i < n; i++) {
            baseProfit += 1LL * strategy[i] * prices[i];
        }

        // Prefix sums
        vector<long long> profitPrefix(n + 1, 0);
        vector<long long> pricePrefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            profitPrefix[i + 1] = profitPrefix[i] + 1LL * strategy[i] * prices[i];
            pricePrefix[i + 1] = pricePrefix[i] + prices[i];
        }

        long long maxGain = 0;
        int half = k / 2;

        for (int l = 0; l + k <= n; l++) {
            int mid = l + half;
            int r = l + k;

            long long original =
                profitPrefix[r] - profitPrefix[l];

            long long modified =
                pricePrefix[r] - pricePrefix[mid];

            long long gain = modified - original;
            maxGain = max(maxGain, gain);
        }

        return baseProfit + maxGain;
    }
};
