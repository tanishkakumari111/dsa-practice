#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> getSneakyNumbers(vector<int>& nums) {
        int n = nums.size();
        vector<int> freq(n, 0);     // since nums[i] < n
        vector<int> ans;

        for (int x : nums) {
            freq[x]++;
            if (freq[x] == 2)       // found a duplicate
                ans.push_back(x);
        }

        return ans;
    }
};
