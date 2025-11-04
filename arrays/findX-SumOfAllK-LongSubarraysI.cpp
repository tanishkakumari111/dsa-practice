class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        unordered_map<int, int> freq;
        vector<long long> res;

        for (int i = 0; i < n; i++) {
            freq[nums[i]]++;
            if (i >= k) {
                // Remove element that slides out of window
                if (--freq[nums[i - k]] == 0) freq.erase(nums[i - k]);
            }
            if (i >= k - 1) {
                // Compute X-sum for current window
                vector<pair<int,int>> f(freq.begin(), freq.end());
                
                // Sort by frequency desc, then by value desc
                sort(f.begin(), f.end(), [](auto &a, auto &b){
                    if (a.second == b.second) return a.first > b.first;
                    return a.second > b.second;
                });

                long long sum = 0;
                for (int j = 0; j < min(x, (int)f.size()); j++) {
                    sum += 1LL * f[j].first * f[j].second;
                }

                res.push_back(sum);
            }
        }
        return res;
    }
};
