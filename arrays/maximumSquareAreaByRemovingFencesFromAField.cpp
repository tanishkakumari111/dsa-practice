class Solution {
public:
    static constexpr int mod = 1e9 + 7;
    unordered_set<int> seen;
    int maxL = 0;

    void findLen(vector<int>& fences, int sz, bool isVertical) {
        sort(fences.begin(), fences.end());
        for (int l = 0; l < sz - 1; l++) {
            for (int r = l + 1; r < sz; r++) {
                int len = fences[r] - fences[l];
                if (isVertical) {
                    if (len > maxL && seen.count(len)) {
                        maxL = len;
                    }
                } else {
                    seen.insert(len);
                }
            }
        }
    }

    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);

        // Process horizontal fences first to populate the set
        findLen(hFences, hFences.size(), false);
        // Process vertical fences to find the max common length
        findLen(vFences, vFences.size(), true);

        if (maxL == 0) return -1;
        return (long long)maxL * maxL % mod;
    }
};
