class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;

        sort(nums.begin(), nums.end());
        int ans = 0;

        // k is the index of the largest side
        for (int k = n - 1; k >= 2; --k) {
            int i = 0, j = k - 1;
            while (i < j) {
                long long sum = (long long)nums[i] + nums[j];
                if (sum > nums[k]) {
                    // All indices t in [i, j-1] with current j are valid
                    ans += (j - i);
                    --j;
                } else {
                    ++i;
                }
            }
        }
        return ans;
    }
};

// Notes / Edge cases
// 1. If zeros or non-positive lengths allowed: a side length of 0 cannot form a triangle — sorting and the same checks handle this automatically (0s won't satisfy sums).
// 2. Use long long for sum to avoid overflow if values are large (above 2e9).
