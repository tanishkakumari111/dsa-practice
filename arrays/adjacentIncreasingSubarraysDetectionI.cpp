class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        if (n < 2 * k) return false;

        vector<int> inc(n, 1);
        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) inc[i] = inc[i - 1] + 1;
        }

        for (int i = 0; i + 2 * k - 1 < n; i++) {
            // check subarray i..i+k-1 and i+k..i+2k-1
            if (inc[i + k - 1] >= k && inc[i + 2 * k - 1] >= k) {
                // but also make sure second subarray starts after the first
                // and does not rely on previous increasing sequence
                // so check inc[i + 2*k - 1] >= k means it ends at i+2k-1 with length >= k
                // but also starting index of second subarray must be i+k
                if (inc[i + 2 * k - 1] - inc[i + k - 1] <= k) {
                    // For second subarray, it needs to be increasing starting at i+k exactly.
                    // We can directly check: inc[i+2k-1] >= k is enough because if the streak 
                    // passes the boundary, it's still valid.
                    return true;
                }
            }
        }
        return false;
    }
};
