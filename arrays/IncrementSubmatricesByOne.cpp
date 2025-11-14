class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> diff(n + 1, vector<int>(n + 1, 0));

        // Apply difference updates for each query
        for (auto &q : queries) {
            int r1 = q[0], c1 = q[1];
            int r2 = q[2], c2 = q[3];

            diff[r1][c1] += 1;
            diff[r1][c2 + 1] -= 1;
            diff[r2 + 1][c1] -= 1;
            diff[r2 + 1][c2 + 1] += 1;
        }

        // Prefix sum over rows
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                diff[i][j] += diff[i][j - 1];
            }
        }

        // Prefix sum over columns
        for (int j = 0; j < n; j++) {
            for (int i = 1; i < n; i++) {
                diff[i][j] += diff[i - 1][j];
            }
        }

        // Remove extra row/column and return result
        vector<vector<int>> res(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                res[i][j] = diff[i][j];

        return res;
    }
};
