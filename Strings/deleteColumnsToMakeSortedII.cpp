#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size();
        int m = strs[0].size();

        vector<bool> sorted(n - 1, false);
        int deletions = 0;

        for (int c = 0; c < m; c++) {
            bool bad = false;

            // Check for violation
            for (int r = 0; r < n - 1; r++) {
                if (!sorted[r] && strs[r][c] > strs[r + 1][c]) {
                    bad = true;
                    break;
                }
            }

            if (bad) {
                deletions++;
                continue;
            }

            // Update sorted pairs
            for (int r = 0; r < n - 1; r++) {
                if (!sorted[r] && strs[r][c] < strs[r + 1][c]) {
                    sorted[r] = true;
                }
            }
        }

        return deletions;
    }
};
