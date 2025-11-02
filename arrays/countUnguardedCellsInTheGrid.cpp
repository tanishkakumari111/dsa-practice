class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<int>> grid(m, vector<int>(n, 0));

        // Mark guards and walls
        for (auto& g : guards) grid[g[0]][g[1]] = 1;
        for (auto& w : walls) grid[w[0]][w[1]] = 2;

        // Directions: up, down, left, right
        vector<pair<int,int>> dirs = {{-1,0},{1,0},{0,-1},{0,1}};

        for (auto& g : guards) {
            int r = g[0], c = g[1];
            for (auto& [dr, dc] : dirs) {
                int i = r + dr, j = c + dc;
                while (i >= 0 && i < m && j >= 0 && j < n) {
                    if (grid[i][j] == 1 || grid[i][j] == 2) break; // stop at guard or wall
                    if (grid[i][j] == 0) grid[i][j] = 3; // mark guarded
                    i += dr;
                    j += dc;
                }
            }
        }

        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0)
                    count++;
            }
        }
        return count;
    }
};
