class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        double low = 1e9, high = -1e9;

        for (auto& s : squares) {
            low = min(low, (double)s[1]);
            high = max(high, (double)(s[1] + s[2]));
        }

        for (int iter = 0; iter < 80; ++iter) { // sufficient precision
            double mid = (low + high) / 2.0;
            double below = 0.0, above = 0.0;

            for (auto& s : squares) {
                double y = s[1], len = s[2];
                double total = len * len;

                if (mid <= y) {
                    above += total;
                } else if (mid >= y + len) {
                    below += total;
                } else {
                    below += (mid - y) * len;
                    above += total - (mid - y) * len;
                }
            }

            if (above > below)
                low = mid;
            else
                high = mid;
        }

        return (low + high) / 2.0;
    }
};
