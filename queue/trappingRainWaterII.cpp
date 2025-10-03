class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        if (m == 0) return 0;
        int n = heightMap[0].size();
        if (n == 0) return 0;

        // Min-heap (height, x, y)
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // Step 1: Add all border cells
        for (int i = 0; i < m; i++) {
            pq.push({heightMap[i][0], i, 0});
            pq.push({heightMap[i][n - 1], i, n - 1});
            visited[i][0] = visited[i][n - 1] = true;
        }
        for (int j = 1; j < n - 1; j++) {
            pq.push({heightMap[0][j], 0, j});
            pq.push({heightMap[m - 1][j], m - 1, j});
            visited[0][j] = visited[m - 1][j] = true;
        }

        int res = 0;
        vector<int> dirs = {0, 1, 0, -1, 0};

        // Step 2: Process heap
        while (!pq.empty()) {
            auto cell = pq.top();
            pq.pop();
            int h = cell[0], x = cell[1], y = cell[2];

            for (int k = 0; k < 4; k++) {
                int nx = x + dirs[k], ny = y + dirs[k + 1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    // If neighbor lower, trap water
                    if (heightMap[nx][ny] < h) {
                        res += h - heightMap[nx][ny];
                    }
                    // Push updated boundary height
                    pq.push({max(heightMap[nx][ny], h), nx, ny});
                }
            }
        }

        return res;
    }
};
