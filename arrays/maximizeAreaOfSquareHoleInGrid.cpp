class Solution {
public:
    int longestConsecutive(vector<int>& a) {
        sort(a.begin(), a.end());
        int best = 1, cur = 1;
        for (int i = 1; i < a.size(); i++) {
            if (a[i] == a[i - 1] + 1) {
                cur++;
            } else {
                cur = 1;
            }
            best = max(best, cur);
        }
        return best;
    }

    int maximizeSquareHoleArea(int n, int m,
                               vector<int>& hBars,
                               vector<int>& vBars) {
        int maxH = longestConsecutive(hBars) + 1;
        int maxV = longestConsecutive(vBars) + 1;
        int side = min(maxH, maxV);
        return side * side;
    }
};
