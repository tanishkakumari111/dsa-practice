class Solution {
public:
    int maxFreqSum(string s) {
        unordered_map<char, int> freq;
        int maxVowel = 0, maxConsonant = 0;
        string vowels = "aeiou";

        // Count frequency of each character
        for (char c : s) {
            freq[c]++;
        }

        // Find max frequency for vowels and consonants
        for (auto& [c, count] : freq) {
            if (vowels.find(c) != string::npos) {
                maxVowel = max(maxVowel, count);
            } else {
                maxConsonant = max(maxConsonant, count);
            }
        }

        return maxVowel + maxConsonant;
    }
};
