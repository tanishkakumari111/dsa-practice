class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int count = 0;

        for (int i = 0; i + 2 < m; ++i) {
            for (int j = 0; j + 2 < n; ++j) {
                if (isMagic(grid, i, j))
                    count++;
            }
        }
        return count;
    }

private:
    bool isMagic(vector<vector<int>>& g, int r, int c) {
        // center must be 5
        if (g[r + 1][c + 1] != 5)
            return false;

        vector<bool> seen(10, false);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int val = g[r + i][c + j];
                if (val < 1 || val > 9 || seen[val])
                    return false;
                seen[val] = true;
            }
        }

        // rows
        for (int i = 0; i < 3; ++i)
            if (g[r + i][c] + g[r + i][c + 1] + g[r + i][c + 2] != 15)
                return false;

        // columns
        for (int j = 0; j < 3; ++j)
            if (g[r][c + j] + g[r + 1][c + j] + g[r + 2][c + j] != 15)
                return false;

        // diagonals
        if (g[r][c] + g[r + 1][c + 1] + g[r + 2][c + 2] != 15)
            return false;

        if (g[r][c + 2] + g[r + 1][c + 1] + g[r + 2][c] != 15)
            return false;

        return true;
    }
};
