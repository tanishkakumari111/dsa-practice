class Solution {
public:
    int countNegatives(vector<vector<int>>& matrix) {
        int negativeCount = 0;
        int columnCount = matrix[0].size();
        int negativeStartIndex = columnCount - 1;
    
        for (auto& eachRow : matrix) {
            while (negativeStartIndex >= 0 && eachRow[negativeStartIndex] < 0) {
                negativeStartIndex--;
            }
            negativeCount += (columnCount - (negativeStartIndex + 1));
        }
        return negativeCount;
    }
};
