class Solution {
public:
    int count;
    int k;

    int dfs(int u, int parent, vector<vector<int>>& adj, vector<int>& values) {
        long long sum = values[u];

        for (int v : adj[u]) {
            if (v == parent) continue;
            long long child = dfs(v, u, adj, values);
            sum += child;
        }

        if (sum % k == 0) {
            count++;       // form a component
            return 0;      // cut from parent
        }

        return sum % k;    // pass remainder upward
    }

    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        this->k = k;
        count = 0;

        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(0, -1, adj, values);
        return count;
    }
};
