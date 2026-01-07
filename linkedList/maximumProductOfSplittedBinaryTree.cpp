class Solution {
public:
    int maxProduct(TreeNode* root) {
        totalSum = treeSum(root);
        dfs(root);
        return maxProd % MOD;
    }

private:
    const int MOD = 1e9 + 7;
    long long totalSum = 0;
    long long maxProd = 0;

    long long treeSum(TreeNode* node) {
        if (!node) return 0;
        return node->val + treeSum(node->left) + treeSum(node->right);
    }

    long long dfs(TreeNode* node) {
        if (!node) return 0;

        long long subSum =
            node->val + dfs(node->left) + dfs(node->right);

        maxProd = max(maxProd, subSum * (totalSum - subSum));
        return subSum;
    }
};
