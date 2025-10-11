class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        unordered_map<int, long long> freq;
        for (int p : power) freq[p]++;

        vector<int> keys;
        for (auto &it : freq) keys.push_back(it.first);
        sort(keys.begin(), keys.end());

        int n = keys.size();
        vector<long long> total(n), dp(n);

        for (int i = 0; i < n; ++i)
            total[i] = (long long)keys[i] * freq[keys[i]];

        for (int i = 0; i < n; ++i) {
            // Option 1: don't pick current
            long long option1 = (i > 0 ? dp[i - 1] : 0);

            // Option 2: pick current
            int lo = 0, hi = i - 1, j = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (keys[i] - keys[mid] > 2) {
                    j = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            long long option2 = total[i] + (j >= 0 ? dp[j] : 0);

            dp[i] = max(option1, option2);
        }

        return dp[n - 1];
    }
};
