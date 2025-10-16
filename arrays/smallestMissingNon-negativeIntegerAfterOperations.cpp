/*Key Insight
Let’s think in terms of remainders modulo value.

For example, if value = 3,
any number x can be transformed into x + k*3 or x - k*3 →
so all numbers with the same remainder modulo 3 are interchangeable.

👉 Therefore, the problem reduces to:
“Given counts of numbers for each remainder r = nums[i] % value,
find the smallest non-negative integer that cannot be represented using these remainders.” */

class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        vector<int> freq(value, 0);

        // Step 1: Count frequency of remainders
        for (int x : nums) {
            int r = ((x % value) + value) % value; // handle negative numbers
            freq[r]++;
        }

        // Step 2: Start checking from 0 upwards
        int x = 0;
        while (true) {
            int r = x % value;
            if (freq[r] > 0) {
                freq[r]--;
                x++;
            } else {
                return x;
            }
        }
    }
};

/*Summary of How I Derived the Logic:
Notice adding/subtracting value preserves remainder mod value.
Reduce problem to remainder buckets.
Count frequency of each remainder.
Greedily try to “assign” each number starting from x = 0.
The first remainder bucket that runs out gives the answer.*/
