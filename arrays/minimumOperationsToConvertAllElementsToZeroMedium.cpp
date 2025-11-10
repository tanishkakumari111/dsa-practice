#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ops = 0;
        vector<int> st; // use vector as stack

        for (int v : nums) {
            if (v == 0) {
                // zero separates regions: clear stack
                st.clear();
                continue;
            }
            // pop larger values (they cannot survive past this smaller v)
            while (!st.empty() && st.back() > v) st.pop_back();

            if (st.empty() || st.back() < v) {
                // we need a new operation for this new value
                st.push_back(v);
                ++ops;
            }
            // if st.back() == v, do nothing (already counted)
        }

        return ops;
    }
};
