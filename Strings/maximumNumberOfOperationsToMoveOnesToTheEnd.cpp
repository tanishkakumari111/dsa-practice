class Solution {
public:
    long long maxOperations(const string &s) {
        long long ans = 0;
        long long ones = 0;
        int n = s.size();

        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') {
                ++ones;
            } else { // s[i] == '0'
                // if this zero is the last in its zero-block (next is '1' or end),
                // it contributes `ones` operations.
                if (i == n - 1 || s[i + 1] == '1') ans += ones;
            }
        }
        return ans;
    }
};
