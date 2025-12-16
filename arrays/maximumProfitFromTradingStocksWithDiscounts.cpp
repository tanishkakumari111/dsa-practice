class Solution {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future,
                  vector<vector<int>>& hierarchy, int budget) {
        // Build the tree
        vector<vector<int>> children(n);
        for (auto &edge : hierarchy) {
            int u = edge[0] - 1;
            int v = edge[1] - 1;
            children[u].push_back(v);
        }

        // DFS returns a pair of DP arrays:
        //  first : dpNoDiscount for this subtree
        //  second: dpWithDiscount for this subtree.
        function<pair<vector<int>, vector<int>>(int)> dfs =
        [&](int u) -> pair<vector<int>, vector<int>> {
            // base dp: no children => zero profit
            vector<int> dpNo(budget + 1, 0), dpYes(budget + 1, 0);

            // Merge child results
            for (int v : children[u]) {
                auto [childNo, childYes] = dfs(v);
                // merge dpNo with childNo
                vector<int> newNo(budget + 1, -1e9);
                vector<int> newYes(budget + 1, -1e9);
                for (int b = 0; b <= budget; b++) {
                    if (dpNo[b] < 0) continue;
                    for (int cb = 0; cb + b <= budget; cb++) {
                        newNo[b + cb] = max(newNo[b + cb], dpNo[b] + childNo[cb]);
                        newYes[b + cb] = max(newYes[b + cb], dpYes[b] + childNo[cb]);
                    }
                }
                dpNo.swap(newNo);
                dpYes.swap(newYes);
            }

            // Now consider buying current node u
            vector<int> resNo(dpNo), resYes(dpYes);
            int fullCost = present[u];
            int discountCost = present[u] / 2;
            int profitFull = future[u] - fullCost;
            int profitDisc = future[u] - discountCost;

            // Buy u at full cost (makes children discounted)
            for (int b = fullCost; b <= budget; b++) {
                resNo[b] = max(resNo[b], dpYes[b - fullCost] + profitFull);
            }
            // Buy u at discount (only if parent bought)
            for (int b = discountCost; b <= budget; b++) {
                resYes[b] = max(resYes[b], dpYes[b - discountCost] + profitDisc);
            }

            return make_pair(resNo, resYes);
        };

        auto [rootNo, rootYes] = dfs(0);
        // rootYes is meaningless for root since no parent exists for discount;
        // answer is max over dpNo ≤ budget.
        int answer = 0;
        for (int b = 0; b <= budget; b++) {
            answer = max(answer, rootNo[b]);
        }
        return answer;
    }
};
