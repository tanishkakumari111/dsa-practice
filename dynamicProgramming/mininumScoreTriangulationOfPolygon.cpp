class Solution {
public:
    int n;
    vector<vector<int>> memo;

    int dfs(vector<int>& v, int i, int j) {
        if (j - i < 2) return 0;
        if (memo[i][j] != -1) return memo[i][j];

        int res = INT_MAX;
        for (int k = i+1; k < j; k++) {
            res = min(res, dfs(v,i,k) + dfs(v,k,j) + v[i]*v[j]*v[k]);
        }
        return memo[i][j] = res;
    }

    int minScoreTriangulation(vector<int>& values) {
        n = values.size();
        memo.assign(n, vector<int>(n, -1));
        return dfs(values, 0, n-1);
    }
};
