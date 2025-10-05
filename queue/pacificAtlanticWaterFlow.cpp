class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> pac(m, vector<int>(n, 0)), atl(m, vector<int>(n, 0));
        queue<pair<int,int>> qPac, qAtl;
        vector<int> dirs = {0, 1, 0, -1, 0};

        // Initialize boundaries
        for (int i = 0; i < m; i++) {
            qPac.push({i, 0});
            qAtl.push({i, n - 1});
            pac[i][0] = atl[i][n - 1] = 1;
        }
        for (int j = 0; j < n; j++) {
            qPac.push({0, j});
            qAtl.push({m - 1, j});
            pac[0][j] = atl[m - 1][j] = 1;
        }

        auto bfs = [&](queue<pair<int,int>>& q, vector<vector<int>>& visited) {
            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                for (int k = 0; k < 4; k++) {
                    int nx = x + dirs[k], ny = y + dirs[k + 1];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                        !visited[nx][ny] &&
                        heights[nx][ny] >= heights[x][y]) {
                        visited[nx][ny] = 1;
                        q.push({nx, ny});
                    }
                }
            }
        };

        bfs(qPac, pac);
        bfs(qAtl, atl);

        vector<vector<int>> res;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pac[i][j] && atl[i][j]) res.push_back({i, j});
            }
        }

        return res;
    }
};
