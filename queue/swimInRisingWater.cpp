class Solution {
public:
    bool canReach(vector<vector<int>>& grid, int t) {
        int n = grid.size();
        if (grid[0][0] > t) return false;
        queue<pair<int,int>> q;
        vector<vector<int>> vis(n, vector<int>(n, 0));
        q.push({0,0}); vis[0][0] = 1;
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        while (!q.empty()) {
            auto [x,y] = q.front(); q.pop();
            if (x == n-1 && y == n-1) return true;
            for (auto &d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && !vis[nx][ny] && grid[nx][ny] <= t) {
                    vis[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }
        return false;
    }

    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int lo = max(grid[0][0], grid[n-1][n-1]), hi = n*n - 1, ans = hi;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (canReach(grid, mid)) ans = mid, hi = mid - 1;
            else lo = mid + 1;
        }
        return ans;
    }

};
