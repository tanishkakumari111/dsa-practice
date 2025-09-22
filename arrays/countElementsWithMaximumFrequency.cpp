class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        unordered_map<int, int> freq;
        int maxCount = 0;

        for(int i: nums){
            freq[i]++;
            maxCount = max(maxCount, freq[i]);
        } 

        int total = 0;
        for (auto &p : freq) {
            if (p.second == maxCount) total += p.second;
        }

        return total;
    }
};
