class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = colors.size();
        int totalTime = 0;
        int i = 0;

        while (i < n) {
            char currentColor = colors[i];
            int groupSum = 0, groupMax = 0;

            // Traverse all same-color balloons
            while (i < n && colors[i] == currentColor) {
                groupSum += neededTime[i];
                groupMax = max(groupMax, neededTime[i]);
                i++;
            }

            // Remove all except the one with max time
            totalTime += (groupSum - groupMax);
        }

        return totalTime;
    }
};
