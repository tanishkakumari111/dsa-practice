class Solution {
public:
    int countPalindromicSubsequence(string s) {
        int n = s.size();
        
        vector<int> first(26, n), last(26, -1);

        // record first and last occurrences
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = max(last[c], i);
        }

        int ans = 0;

        // check for each outer character
        for (int c = 0; c < 26; c++) {
            if (first[c] < last[c]) {
                unordered_set<char> mid;
                for (int i = first[c] + 1; i < last[c]; i++) {
                    mid.insert(s[i]);
                }
                ans += mid.size();
            }
        }

        return ans;
    }
};
