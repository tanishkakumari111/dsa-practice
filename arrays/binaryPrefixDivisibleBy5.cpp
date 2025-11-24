class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& A) {
        vector<bool> ans;
        ans.reserve(A.size());
        
        int mod = 0;
        for (int bit : A) {
            mod = (mod * 2 + bit) % 5;
            ans.push_back(mod == 0);
        }
        
        return ans;
    }
};
