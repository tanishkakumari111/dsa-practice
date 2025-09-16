// Intiuation:
// We need to scan left to right, but every time we merge a pair, the result can become non-coprime with its left neighbor too.
// So it’s like building a stack:
// 1.Push numbers one by one.
// 2.After pushing, while stack has at least 2 elements and top two are non-coprime:
// 3.Pop the top two, replace with their LCM, push back.
// 4.Continue until no merge possible.

// Complexity:
// Time: O(n * α) essentially O(n log(max(nums))) because each merge does gcd.
// Space: O(n) for the stack.

  
class Solution {
public:
    int gcd(long long a, long long b){
        while(b != 0){
            long long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    vector<int> replaceNonCoprimes(vector<int>& nums) {
        vector<long long> stack;

        for(long long x: nums){
            stack.push_back(x);

            while(stack.size() >= 2){
                long long a = stack.back(); stack.pop_back();
                long long b = stack.back(); stack.pop_back();
                long long g = gcd(a,b);

                if(g > 1){
                    long long lcm = a / g * b; // lcm
                    stack.push_back(lcm);
                }
                else{
                    stack.push_back(b);
                    stack.push_back(a);
                    break; //stop when co-prime
                }
            }
        }
        vector<int> ans(stack.begin(), stack.end());
        return ans;
    }
};
