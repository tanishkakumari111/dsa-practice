/*
🔑 Idea
1. Precompute inc[i] = length of strictly increasing subarray starting at index i. ✅ O(n)
2. The answer is the maximum k such that there exists i with:

-----> inc[i] >= k  AND  inc[i+k] >= k

3. Since larger k implies stricter condition, we can binary search k from 1 to n/2.
4. For a given k, scan i = 0 → n - 2*k and check if condition holds. ✅ O(n) per check

Total complexity = O(n log n)
*/

class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> inc(n,1);
        
        // Compute increasing streaks from each index
        for(int i = n-2; i >= 0; --i){
            if(nums[i] < nums[i+1]){
                inc[i] = inc[i+1]+1;
            }
        }
        
        int left = 1, right = n/2;
        int ans = 0;
        
        while(left <= right){
            int mid = left + (right-left)/2;
            bool found = false;
            
            // Check if there exists i with inc[i] >= mid and inc[i+mid] >= mid
            for(int i = 0; i + 2*mid <= n; ++i){
                if(inc[i] >= mid && inc[i+mid] >= mid){
                    found = true;
                    break;
                }
            }
            
            if(found){
                ans = mid;      // mid is possible
                left = mid + 1; // try bigger k
            }else{
                right = mid - 1; // try smaller k
            }
        }
        
        return ans;
    }
};

/*
⏳ Complexity
Time: O(n log n) → O(n) to build inc, O(n) to check each mid, log n binary search steps
Space: O(n) for inc array

This handles tricky plateaus and large arrays efficiently.
If you want, I can also show a truly O(n) solution without binary search, which finds max k in a single pass. It’s a bit trickier but fastest possible. (SLIDING WINDOW)

✅ Key Insight:
By precomputing the increasing streak lengths and moving through each streak, we can determine the max possible k for adjacent increasing subarrays in one pass.
This handles tricky plateaus automatically and avoids binary search.
*/
