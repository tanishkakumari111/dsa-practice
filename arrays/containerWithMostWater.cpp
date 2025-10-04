class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxWater=0, i=0, j=height.size()-1;
        while(i<j){
            int water=(min(height[i], height[j]))*(j-i);
            maxWater=max(maxWater, water);
            height[i]<height[j]?i++:j--;
        }
        return maxWater;
    }
};
