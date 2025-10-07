class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        vector<int> ans(n, 1);
        unordered_map<int, int> lakeFull;
        unordered_map<int, queue<int>> futureRains;

        // Step 1: store all future rains
        for (int i = 0; i < n; i++) {
            if (rains[i] > 0)
                futureRains[rains[i]].push(i);
        }

        set<pair<int,int>> nextRainSet;  // {nextRainDay, lake}

        for (int i = 0; i < n; i++) {
            if (rains[i] > 0) {
                int lake = rains[i];
                ans[i] = -1;
                futureRains[lake].pop(); // remove today’s rain
                
                if (lakeFull.count(lake)) {
                    // this lake is already full → flood
                    return {};
                }

                // mark full
                lakeFull[lake] = i;

                // add next rain of this lake
                if (!futureRains[lake].empty()) {
                    nextRainSet.insert({futureRains[lake].front(), lake});
                }

            } else {
                // dry a lake
                if (!nextRainSet.empty()) {
                    auto it = nextRainSet.begin();
                    int lakeToDry = it->second;
                    ans[i] = lakeToDry;
                    lakeFull.erase(lakeToDry);
                    nextRainSet.erase(it);
                } else {
                    ans[i] = 1; // arbitrary
                }
            }
        }

        return ans;
    }
};
