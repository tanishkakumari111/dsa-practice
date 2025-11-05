#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // comparator: higher freq first; on tie higher value first
    struct Cmp {
        bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
            if (a.first != b.first) return a.first > b.first;
            return a.second > b.second;
        }
    };

    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        unordered_map<int,int> freq;                 // val -> freq
        multiset<pair<int,int>, Cmp> top;           // top elements (best first at begin())
        multiset<pair<int,int>, Cmp> bottom;        // rest (best first at begin())
        long long topSum = 0;                       // sum of freq*val for pairs in 'top'
        vector<long long> ans;

        auto removePair = [&](const pair<int,int>& p) {
            // try to erase from top first
            auto itTop = top.find(p);
            if (itTop != top.end()) {
                topSum -= 1LL * itTop->first * itTop->second;
                top.erase(itTop);
                return;
            }
            auto itBot = bottom.find(p);
            if (itBot != bottom.end()) bottom.erase(itBot);
        };

        auto rebalance = [&]() {
            int desired = min((int)freq.size(), x);

            // 1) demote while top oversized
            while ((int)top.size() > desired) {
                auto worst = prev(top.end());         // worst in top because sorted best-first
                pair<int,int> p = *worst;
                topSum -= 1LL * p.first * p.second;
                top.erase(worst);
                bottom.insert(p);
            }

            // 2) promote best from bottom while top needs elements
            while ((int)top.size() < desired && !bottom.empty()) {
                auto bestBot = bottom.begin();       // best in bottom
                pair<int,int> p = *bestBot;
                bottom.erase(bestBot);
                top.insert(p);
                topSum += 1LL * p.first * p.second;
            }

            // 3) swap if best(bottom) is better than worst(top)
            while (!bottom.empty() && !top.empty()) {
                auto bestBot = bottom.begin();
                auto worstTop = prev(top.end());
                // if bottom.best is strictly better than top.worst, swap them
                // comparator returns true if a is "better" than b
                if (Cmp()(*bestBot, *worstTop)) {
                    pair<int,int> pb = *bestBot;
                    pair<int,int> pt = *worstTop;
                    // move worstTop -> bottom, bestBot -> top
                    bottom.erase(bestBot);
                    top.erase(worstTop);
                    // update topSum
                    topSum -= 1LL * pt.first * pt.second;
                    top.insert(pb);
                    bottom.insert(pt);
                    topSum += 1LL * pb.first * pb.second;
                } else break;
            }
        };

        auto updateFreq = [&](int val, int delta) {
            int oldF = freq.count(val) ? freq[val] : 0;
            if (oldF > 0) {
                // remove old pair (oldF, val) from whichever set it resides in
                removePair({oldF, val});
            }
            int newF = oldF + delta;
            if (newF <= 0) {
                if (freq.count(val)) freq.erase(val);
            } else {
                freq[val] = newF;
                // insert new pair into bottom; rebalance will place it correctly
                bottom.insert({newF, val});
            }
            rebalance();
        };

        for (int i = 0; i < n; ++i) {
            // add nums[i]
            updateFreq(nums[i], +1);

            if (i >= k) {
                // remove nums[i-k]
                updateFreq(nums[i - k], -1);
            }

            if (i >= k - 1) {
                ans.push_back(topSum);
            }
        }

        return ans;
    }
};
