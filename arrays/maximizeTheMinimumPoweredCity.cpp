#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxPower(vector<int>& stations, int r, int k) {
        int n = stations.size();
        vector<long long> power(n, 0);

        // Step 1: Compute initial power at each city
        long long window = 0;
        for (int i = 0; i < n; ++i) {
            window += stations[i];
            if (i - r - 1 >= 0) window -= stations[i - r - 1];
            if (i + r < n) power[i + r] = window;  // shift ahead, fill after loop
        }

        // Actually fix the above to correct sliding window:
        window = 0;
        for (int i = 0; i < n; ++i) {
            int left = max(0, i - r);
            int right = min(n - 1, i + r);
            // Instead of recalculating O(n*r), let's do efficient prefix sum.
        }

        // Let's recompute efficiently using prefix sums:
        vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + stations[i];
        for (int i = 0; i < n; ++i) {
            int l = max(0, i - r);
            int rr = min(n - 1, i + r);
            power[i] = pref[rr + 1] - pref[l];
        }

        // Step 2: Binary search
        long long lo = 0, hi = 1e18, ans = 0;
        while (lo <= hi) {
            long long mid = (lo + hi) / 2;
            if (canAchieve(power, r, k, mid)) {
                ans = mid;
                lo = mid + 1;
            } else hi = mid - 1;
        }
        return ans;
    }

private:
    bool canAchieve(vector<long long> power, int r, long long k, long long x) {
        int n = power.size();
        vector<long long> add(n, 0);
        long long used = 0, extra = 0;

        for (int i = 0; i < n; ++i) {
            extra += add[i]; // accumulated from diff array
            long long curr = power[i] + extra;
            if (curr < x) {
                long long need = x - curr;
                used += need;
                if (used > k) return false;
                extra += need;
                if (i + 2LL * r + 1 < n)
                    add[i + 2LL * r + 1] -= need;  // stop affecting after this point
            }
        }
        return true;
    }
};
