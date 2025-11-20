class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        // Sort by right asc, left desc
        sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
            if (a[1] == b[1]) return a[0] > b[0];
            return a[1] < b[1];
        });

        int a = -1, b = -1;   // last two points chosen
        int count = 0;

        for (auto &in : intervals) {
            int L = in[0], R = in[1];

            bool hasA = (a >= L && a <= R);
            bool hasB = (b >= L && b <= R);

            if (hasA && hasB) {
                continue;
            }

            if (hasA || hasB) {
                // only one point inside → add R
                count += 1;
                b = a;
                a = R;
            } else {
                // none inside → add R-1, R
                count += 2;
                b = R - 1;
                a = R;
            }
        }

        return count;
    }
};
