class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long sumAbs = 0;
        int negCount = 0;
        int minAbs = INT_MAX;

        for (auto& row : matrix) {
            for (int x : row) {
                sumAbs += llabs(x);
                if (x < 0) negCount++;
                minAbs = min(minAbs, abs(x));
            }
        }

        if (negCount % 2 == 0)
            return sumAbs;

        return sumAbs - 2LL * minAbs;
    }
};
