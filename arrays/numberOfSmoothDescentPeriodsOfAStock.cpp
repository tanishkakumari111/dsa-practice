class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {
        long long ans = 0;
        long long len = 1; // length of current smooth descent

        for (int i = 0; i < prices.size(); i++) {
            if (i > 0 && prices[i] == prices[i - 1] - 1) {
                len++;
            } else {
                len = 1;
            }
            ans += len;
        }

        return ans;
    }
};
