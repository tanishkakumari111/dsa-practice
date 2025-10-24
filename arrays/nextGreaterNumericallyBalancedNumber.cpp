class Solution {
public:
    int nextBeautifulNumber(int n) {
        vector<long long> balanced;
        // digits 1..9 -> index 0..8 represent digit d = idx+1
        for (int mask = 1; mask < (1 << 9); ++mask) {
            int totalLen = 0;
            for (int i = 0; i < 9; ++i) if (mask & (1 << i)) totalLen += (i + 1);
            if (totalLen == 0 || totalLen > 10) continue; // keep length reasonable (<=10)
            
            // build multiset vector of digits
            vector<int> arr;
            arr.reserve(totalLen);
            for (int i = 0; i < 9; ++i) {
                if (mask & (1 << i)) {
                    int d = i + 1;
                    for (int k = 0; k < d; ++k) arr.push_back(d);
                }
            }
            sort(arr.begin(), arr.end());
            
            // generate all unique permutations of arr
            do {
                // skip numbers with leading zero - not applicable since digits are 1..9
                long long val = 0;
                for (int x : arr) {
                    val = val * 10 + x;
                    if (val > 2000000000LL) break; // guard (not strictly necessary)
                }
                balanced.push_back(val);
            } while (next_permutation(arr.begin(), arr.end()));
        }
        
        // sort and unique
        sort(balanced.begin(), balanced.end());
        balanced.erase(unique(balanced.begin(), balanced.end()), balanced.end());
        
        // find smallest > n
        auto it = upper_bound(balanced.begin(), balanced.end(), n);
        if (it == balanced.end()) return -1; // problem guarantee typically ensures one exists; otherwise return -1
        return (int)(*it);
    }
};
