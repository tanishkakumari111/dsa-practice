constexpr int MX = 100001;
int divisor_num[MX];
int divisor_sum[MX];

// Precompute divisor counts and sums for all numbers up to 100,000
int init = [] {
    for (int i = 1; i < MX; i++) {
        for (int j = i; j < MX; j += i) {
            divisor_num[j]++; 
            divisor_sum[j] += i;
        }
    }
    return 0;
}();

class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int ans = 0;
        for (int x : nums) {
            if (x < MX && divisor_num[x] == 4) {
                ans += divisor_sum[x];
            }
        }
        return ans;
    }
};
