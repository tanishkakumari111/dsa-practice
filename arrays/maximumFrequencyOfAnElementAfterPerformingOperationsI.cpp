class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        unordered_map<int,int> cnt;
        map<int,int> diff; // ordered map for sweep-line

        for (int v : nums) {
            cnt[v]++;
            diff[v - k]++;         // start (inclusive)
            diff[v + k + 1]--;     // end (exclusive)
            diff[v] += 0;          // ensure target value v is evaluated in the sweep
        }

        int ans = 1;
        int curr = 0; // active elements that can reach current x

        for (auto &p : diff) {
            int x = p.first;
            int delta = p.second;
            curr += delta; // number of elements whose interval includes x
            int existing = cnt.count(x) ? cnt[x] : 0;
            int possible = existing + numOperations;
            ans = max(ans, min(curr, possible));
        }
        return ans;
    }
};
