#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007LL;

long long modpow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int popcountll(long long x){
    return __builtin_popcountll((unsigned long long)x);
}

class Solution {
public:
    int magicalSum(int m, int k, vector<int>& nums) {
        int n = (int)nums.size();

        // Precompute factorials and inverse factorials up to m
        vector<long long> fact(m+1,1), invfact(m+1,1);
        for (int i=1;i<=m;i++) fact[i] = fact[i-1] * i % MOD;
        invfact[m] = modpow(fact[m], MOD-2);
        for (int i=m-1;i>=0;i--) invfact[i] = invfact[i+1] * (i+1) % MOD;

        // Precompute pow(nums[i], t) for t = 0..m
        vector<vector<long long>> powNum(n, vector<long long>(m+1,1));
        for (int i=0;i<n;i++){
            for (int t=1;t<=m;t++){
                powNum[i][t] = powNum[i][t-1] * (nums[i] % MOD) % MOD;
            }
        }

        // DP dimensions:
        // dp[used][carry][ones] = sum of (prod nums^c / prod c! ) for processed positions
        // We'll store only up to ones = k (no need to track beyond k, since we only care exact k when finished)
        // carry maximal value <= m (because at any step, carry <= m)
        int K = k;
        vector<vector<vector<long long>>> dp_prev(m+1,
            vector<vector<long long>>(m+1, vector<long long>(K+1, 0)));
        vector<vector<vector<long long>>> dp_next = dp_prev;

        // initial: no positions processed, used=0, carry=0, ones=0 -> value 1 (empty product)
        dp_prev[0][0][0] = 1;

        for (int pos = 0; pos < n; ++pos) {
            // clear dp_next
            for (int u = 0; u <= m; ++u)
                for (int c = 0; c <= m; ++c)
                    fill(dp_next[u][c].begin(), dp_next[u][c].end(), 0);

            for (int used = 0; used <= m; ++used) {
                for (int carry = 0; carry <= m; ++carry) {
                    for (int ones = 0; ones <= K; ++ones) {
                        long long curVal = dp_prev[used][carry][ones];
                        if (!curVal) continue;

                        // choose t copies of index 'pos'
                        int maxT = m - used;
                        for (int t = 0; t <= maxT; ++t) {
                            int newUsed = used + t;
                            int sumAtPos = carry + t;        // value at this bit position before taking bit and carry
                            int bit = sumAtPos & 1;
                            int newOnes = ones + bit;
                            if (newOnes > K) {
                                // no need to track beyond K (we need exactly K at end)
                                continue;
                            }
                            int newCarry = sumAtPos >> 1;
                            if (newCarry > m) continue; // safety (should not happen)

                            // multiply by nums[pos]^t / t! (we carry inverse factorial)
                            long long mul = powNum[pos][t] * invfact[t] % MOD;
                            long long addv = curVal * mul % MOD;

                            dp_next[newUsed][newCarry][newOnes] += addv;
                            if (dp_next[newUsed][newCarry][newOnes] >= MOD) dp_next[newUsed][newCarry][newOnes] -= MOD;
                        }
                    }
                }
            }
            // swap dp_prev and dp_next
            dp_prev.swap(dp_next);
        }

        // After processing all positions, consider leftover carries.
        long long total = 0;
        for (int carry = 0; carry <= m; ++carry) {
            int carryBits = popcountll(carry);
            for (int ones = 0; ones <= K; ++ones) {
                int finalOnes = ones + carryBits;
                if (finalOnes == K) {
                    // We need used == m
                    long long val = dp_prev[m][carry][ones];
                    if (val) {
                        total += val;
                        if (total >= MOD) total -= MOD;
                    }
                }
            }
        }

        // Multiply by m! to account for ordering permutations (multinomial)
        total = total * fact[m] % MOD;
        return (int)total;
    }
};
