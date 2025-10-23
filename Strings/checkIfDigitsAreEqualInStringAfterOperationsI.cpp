// ---------- modular combination (Lucas theorem) ----------
int nCkModPrime(int n, int k, int p) {
    if (k > n) return 0;
    if (n < p && k < p) {
        // small case: compute directly
        int res = 1;
        for (int i = 1; i <= k; ++i)
            res = res * (n - i + 1) / i;
        return res % p;
    }
    return (nCkModPrime(n / p, k / p, p) * nCkModPrime(n % p, k % p, p)) % p;
}

// combine mod2 and mod5 into mod10
int nCkMod10(int n, int k) {
    int a = nCkModPrime(n, k, 2);
    int b = nCkModPrime(n, k, 5);
    // combine using CRT
    // mod2→a, mod5→b, final mod10 = value satisfying x≡a(mod2), x≡b(mod5)
    for (int x = 0; x < 10; ++x)
        if (x % 2 == a && x % 5 == b) return x;
    return 0;
}

// ---------- main function ----------
class Solution {
public:
    bool hasSameDigits(string s) {
        int n = s.size();
        int leftSum = 0, rightSum = 0;

        for (int i = 0; i + 1 < n; ++i) {
            int coeff = nCkMod10(n - 2, i);
            leftSum = (leftSum + coeff * (s[i] - '0')) % 10;
            rightSum = (rightSum + coeff * (s[i + 1] - '0')) % 10;
        }
        return leftSum == rightSum;
    }
};
