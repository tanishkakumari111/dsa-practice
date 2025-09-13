class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];

        int prev1 = nums[0];
        int prev2 = max(nums[0], nums[1]);

        for(int i=2; i<nums.size(); i++){
            int curr = max(prev2, prev1+nums[i]);
            prev1 = prev2;
            prev2 = curr;
        }

        return prev2;
    }
};

/*
explaination: Step-by-step

[1,2,3,1,2,8]

Initialization:

prev2 = nums[0] = 1

prev1 = max(nums[0], nums[1]) = max(1,2) = 2

Now iterate from i=2 to i=5:

i = 2 (nums[2] = 3):

curr = max(prev1, prev2 + nums[i])
= max(2, 1 + 3)
= max(2,4)
= 4

Update:

prev2 = prev1 = 2

prev1 = curr = 4

i = 3 (nums[3] = 1):

curr = max(prev1, prev2 + nums[i])
= max(4, 2 + 1)
= max(4,3)
= 4

Update:

prev2 = prev1 = 4

prev1 = curr = 4

i = 4 (nums[4] = 2):

curr = max(prev1, prev2 + nums[i])
= max(4, 4 + 2)
= max(4,6)
= 6

Update:

prev2 = prev1 = 4

prev1 = curr = 6

i = 5 (nums[5] = 8):

curr = max(prev1, prev2 + nums[i])
= max(6, 4 + 8)
= max(6,12)
= 12

Update:

prev2 = prev1 = 6

prev1 = curr = 12

Loop ends.

Return prev1 = 12.

Table view
i	nums[i]	prev2 (dp[i-2])	prev1 (dp[i-1])	curr (dp[i])
init	–	1	2	–
2	3	1	2	4
3	1	2	4	4
4	2	4	4	6
5	8	4	6	12

Answer = 12

Intuition:

Best plan:

Rob houses 0 (1) + 2 (3) + 4 (2) + 5 (8)?
Can’t take 4 and 5 together (adjacent).

The optimal selection is houses 2 (3) + 5 (8) + maybe house 1? No.
DP finds max = 12 which corresponds to robbing houses 1 (2) + 4 (2) + 5 (8)? (Actually check: houses 1 and 4 not adjacent? 1 index=1, 4 index=4 → there’s 2 in between, so ok. Houses 4 and 5 adjacent though, so can’t take 4 and 5. The DP result 12 = houses 2 (3) + 5 (8) + ??? or houses 0 (1)+2(3)+5(8)?
The key is DP already solved the constraint. Final max = 12.)

*/
