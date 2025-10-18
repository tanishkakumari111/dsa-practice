class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        int n = nums.size();
        vector<pair<long long,long long>> intervals;
        intervals.reserve(n);

        for (int x : nums) {
            intervals.push_back({(long long)x - k, (long long)x + k});
        }

        sort(intervals.begin(), intervals.end(), [](auto &a, auto &b){
            return a.second < b.second; // sort by right end
        });

        long long last = LLONG_MIN;
        int distinct = 0;

        for (auto &[L, R] : intervals) {
            long long pick = max(L, last + 1);
            if (pick <= R) {
                distinct++;
                last = pick;
            }
        }

        return distinct;
    }
};
