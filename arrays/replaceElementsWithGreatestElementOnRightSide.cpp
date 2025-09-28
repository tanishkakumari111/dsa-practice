class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int n = arr.size();
        int maxElement = arr[n-1];
        for(int i=n-2; i>=0; i--){
            int curr = arr[i];
            arr[i] = maxElement;
            maxElement = max(curr, maxElement);            
        }
        arr[n-1] = -1;

        return arr;
    }
};
