//Approach: Kadane (modified algo)
// This is often called “Kadane’s for product” or modified Kadane.

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxLastPro = 1;
        int minLastPro = 1;
        int ans = nums[0];

        for(int x : nums){
            if(x<0) swap(maxLastPro, minLastPro);
            maxLastPro = max(maxLastPro*x, x);
            minLastPro = min(minLastPro*x, x);

            ans = max(ans, maxLastPro);
        }

        return ans;
    }
};

/*
explantaion:
For product, the sign flips matter.
A large negative number times another negative can become a large positive.
So you must track both max product and min product at each step.

That’s the full algorithm.
It’s exactly the Kadane pattern (keeping a “current best” and resetting on each element), but with an extra track for min because negative * negative = positive.

*/
