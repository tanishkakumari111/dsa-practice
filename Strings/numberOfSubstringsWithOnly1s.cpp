class Solution {
public:
    int numSub(string s) {
        const long long MOD = 1e9 + 7;
        long long result = 0;
        long long len = 0;  // current run of consecutive '1's

        for (char c : s) {
            if (c == '1') {
                len++;
            } else {
                result = (result + (len * (len + 1) / 2) % MOD) % MOD;
                len = 0;
            }
        }

        // add last run if ends with '1'
        result = (result + (len * (len + 1) / 2) % MOD) % MOD;

        return (int)result;
    }
};
