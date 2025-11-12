#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int ones = count(nums.begin(), nums.end(), 1);
        
        // Case 1: Already contains 1s
        if (ones > 0) return n - ones;

        // Case 2: Find shortest subarray with gcd == 1
        int minLen = INT_MAX;
        for (int i = 0; i < n; i++) {
            int g = nums[i];
            for (int j = i + 1; j < n; j++) {
                g = gcd(g, nums[j]);
                if (g == 1) {
                    minLen = min(minLen, j - i + 1);
                    break;
                }
            }
        }

        // No subarray with gcd == 1
        if (minLen == INT_MAX) return -1;

        // (minLen - 1) ops to make one element 1 + (n - 1) to spread it
        return (minLen - 1) + (n - 1);
    }
};
