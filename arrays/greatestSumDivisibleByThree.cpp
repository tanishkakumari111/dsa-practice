class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        long long sum = 0;

        long long r1a = LLONG_MAX, r1b = LLONG_MAX;
        long long r2a = LLONG_MAX, r2b = LLONG_MAX;

        for (long long x : nums) {
            sum += x;

            int r = x % 3;
            if (r == 1) {
                if (x < r1a) { r1b = r1a; r1a = x; }
                else if (x < r1b) r1b = x;
            } 
            else if (r == 2) {
                if (x < r2a) { r2b = r2a; r2a = x; }
                else if (x < r2b) r2b = x;
            }
        }

        if (sum % 3 == 0) return sum;

        long long remove1 = LLONG_MAX, remove2 = LLONG_MAX;

        if (sum % 3 == 1) {
            // option 1: remove smallest remainder-1
            remove1 = r1a;
            // option 2: remove two smallest remainder-2
            if (r2b != LLONG_MAX) remove2 = r2a + r2b;
        } 
        else { // sum % 3 == 2
            // option 1: remove smallest remainder-2
            remove1 = r2a;
            // option 2: remove two smallest remainder-1
            if (r1b != LLONG_MAX) remove2 = r1a + r1b;
        }

        long long best = min(remove1, remove2);
        if (best == LLONG_MAX) return 0; // safety, though shouldn't happen

        return sum - best;
    }
};
