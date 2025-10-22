class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        unordered_map<long long,int> cnt;
        map<long long,int> diff;
        
        for (long long v : nums) {
            cnt[v]++;
            diff[v - k] += 1;
            diff[v + k + 1] -= 1;    // end of interval (exclusive)
            diff[v] += 0;             // ensure we evaluate v as a potential x
        }
        
        int ans = 0;
        long long s = 0;
        for (auto &p : diff) {
            long long x = p.first;
            int delta = p.second;
            s += delta;
            int existing = cnt.count(x) ? cnt[x] : 0;
            // total elements that can reach x = s
            // we can keep existing + up to numOperations conversions
            int possible = existing + numOperations;
            int achievable = (int)min(s, (long long)possible);
            ans = max(ans, achievable);
        }
        return ans;
    }
};
