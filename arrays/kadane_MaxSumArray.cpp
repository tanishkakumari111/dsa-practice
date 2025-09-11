//Approach1: Kadane's Algo
//TC:O(N)
//SC:O(1)
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum = nums[0];
        int maxCurrSum = nums[0];

        for(int i=1; i<nums.size(); i++){
            maxCurrSum = max(nums[i]+maxCurrSum, nums[i]);
            maxSum = max(maxCurrSum, maxSum);
        }

        return maxSum;
    }
};

//Approach2: divide and conquer 
//TC: O(NlogN)
//SC: O(logN)
class Solution {
public:

    int maxCrossingSum(vector<int>& nums, int l, int m, int r) {
        // Compute max sum on left of mid
        int leftSum = INT_MIN, sum = 0;
        for (int i = m; i >= l; i--) {
            sum += nums[i];
            leftSum = max(leftSum, sum);
        }

        // Compute max sum on right of mid
        int rightSum = INT_MIN; sum = 0;
        for (int i = m + 1; i <= r; i++) {
            sum += nums[i];
            rightSum = max(rightSum, sum);
        }

        return leftSum + rightSum;
    }

    int maxSubArrayHelper(vector<int>& nums, int l, int r) {
        if (l == r) return nums[l]; // base case

        int m = l + (r - l) / 2;

        int leftMax = maxSubArrayHelper(nums, l, m);
        int rightMax = maxSubArrayHelper(nums, m + 1, r);
        int crossMax = maxCrossingSum(nums, l, m, r);

        return max({leftMax, rightMax, crossMax});
    }

    int maxSubArray(vector<int>& nums) {
        return maxSubArrayHelper(nums, 0, nums.size() - 1);
    }
};

//            [l........r]
//              /     \
//         [l..mid]  [mid+1..r]

// cross_max = maxSuffix(l..mid) + maxPrefix(mid+1..r)
// return max(left_max, right_max, cross_max)
