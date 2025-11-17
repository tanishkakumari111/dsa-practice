class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        int prev = -1e9; // very small to simulate "no previous 1"
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (nums[i] == 1) {
                if (prev > -1e8) { // we have seen a previous 1
                    if (i - prev - 1 < k) return false;
                }
                prev = i;
            }
        }
        return true;
    }
};
