// my Approach:
class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        int count = 0;
        unordered_map <char, int> map;
        for(char c : brokenLetters) map[c] = 0;
        int flag = 1;
        for( char w : text){
            if(w==' ') {
                if(flag) count++; 
                flag = 1;
            }
            else if(map.find(w)!=map.end()) flag = 0;
            else flag *= 1;
        }
        if(flag) count++; // check last word
        return count;
    }
};

// chatgpt approach:/
class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        // store broken letters in a set
        unordered_set<char> broken(brokenLetters.begin(), brokenLetters.end());
        
        int count = 0;
        bool valid = true; // current word is valid unless proven otherwise
        
        for (char c : text) {
            if (c == ' ') {          // word ended
                if (valid) count++;  // count if valid
                valid = true;        // reset for next word
            } 
            else if (broken.count(c)) {
                valid = false;       // contains broken letter
            }
        }
        // handle last word (no trailing space)
        if (valid) count++;
        
        return count;
    }
};

