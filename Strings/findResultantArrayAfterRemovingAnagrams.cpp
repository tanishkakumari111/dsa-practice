class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words) {
        vector<string> result;
        string prevSorted = "";

        for (auto &word : words) {
            string sortedWord = word;
            sort(sortedWord.begin(), sortedWord.end());

            if (sortedWord != prevSorted) {
                result.push_back(word);
                prevSorted = sortedWord;
            }
        }

        return result;
    }
};
