//Approach-1: Brute force (O(n²))
int maxSubarrayCircularBrute(const vector<int>& nums) {
    int n = nums.size();
    int ans = INT_MIN;
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int len = 0; len < n; ++len) {
            sum += nums[(i + len) % n];
            ans = max(ans, sum);
        }
    }
    return ans;
}


//Approach-2: Kadane’s trick (O(n)) — recommended
class Solution {
public:

    int maxKadane(vector<int>& nums){
        int maxSum = nums[0];
        int maxCurrSum = nums[0];
        for(int i=1; i<nums.size(); i++){
            maxCurrSum = max(maxCurrSum+nums[i], nums[i]);
            maxSum = max(maxSum, maxCurrSum);
        }
        return maxSum;
    }

    int minKadane(vector<int>& nums){
        int minSum = nums[0];
        int minCurrSum = nums[0];
        for(int i=1; i<nums.size(); i++){
            minCurrSum = min(minCurrSum+nums[i], nums[i]);
            minSum = min(minCurrSum, minSum);
        }
        return minSum;
    }
    int maxSubarraySumCircular(vector<int>& nums) {
        int total = 0;
        for (int x : nums) total += x;

        int wrapMax = total-minKadane(nums);
        return wrapMax==0? maxKadane(nums): max(wrapMax,maxKadane(nums));
    }
};
// explaination: Idea (two parts)

// 1. Compute max_normal = maximum subarray sum for the non-circular case (standard Kadane).

// 2.To account for wrap-around subarrays, compute min_subarray (minimum subarray sum). Then wrap_max = total_sum - min_subarray.

// Intuition: a wrap subarray can be seen as total array minus a contiguous block we exclude (the min subarray).
// Answer = max(max_normal, wrap_max). BUT if all numbers are negative then wrap_max becomes 0 (or equals total_sum - total_sum = 0) which is invalid — in that case return max_normal (largest element).

// Important edge case: If min_subarray == total_sum (every element included in min -> all numbers are negative and the min is the whole array), do not use wrap_max — return max_normal.


/*
Exactly 👍 — this is the heart of why the Kadane-style circular trick works.
---
### The idea

A **wrap-around subarray** isn’t one contiguous slice in the original array; it’s made of **the tail of the array + the head of the array**.
For example, in `[5, -3, 5]`, the best wrap subarray is `[5,5]` (index 0 and 2).
If you try to see it as one piece, it’s “after index i” + “before index j”.

But notice:
if you take the **entire array sum** and *remove some contiguous chunk in the middle* (which you don’t want), what’s left is exactly a wrap-around subarray.

---

### Why `wrap_max = total_sum - min_subarray` works

* `total_sum` = sum of all elements
* If you cut out a contiguous block (say indices `l..r`) with **minimum sum**, the remaining parts (before `l` and after `r`) join at the “ends” to form a wrap-around subarray.
* The sum of that wrap-around subarray = `total_sum - (sum of removed block)`
* To make the remaining sum as large as possible, you want to remove the block with the **smallest sum**.
* Hence `wrap_max = total_sum - min_subarray_sum`.

---

### Visual:

```
Array:   [   A   |   B   |   C   ]
          head      (cut)    tail

Total sum = A + B + C
If B is the contiguous block with minimum sum,
wrap sum = A + C = total_sum - B
```

So you compute:

* `max_normal` with regular Kadane → maximum non-wrap sum
* `min_subarray` with “reverse” Kadane → minimum contiguous sum
* `wrap_max = total_sum - min_subarray` → best wrap-around sum

Then you pick `max(max_normal, wrap_max)`.

*(Special case: all numbers negative — you can’t “wrap” because then you’d remove the entire array. That’s why you check `min_subarray == total_sum`.)*

*/
