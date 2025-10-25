class Solution {
public:
    int totalMoney(int n) {
        int w = n / 7;
        int r = n % 7;
        long long full_weeks = 28LL * w + 7LL * (1LL * w * (w - 1) / 2);
        long long rem = 1LL * r * (1 + w) + 1LL * r * (r - 1) / 2;
        return (int)(full_weeks + rem);
    }
};
