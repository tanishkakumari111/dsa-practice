// // Approach 1: Brute Force ->> for logic building
// Complexity:
// For each query, you potentially scan the entire wordlist 3 times.
// If wordlist has n words and queries has m, you’re O(m * n * L) where L = average word length.

/*For each query:
1. Loop through the entire wordlist
2. Check rule 1 (exact)
3. If not found, loop again and check rule 2 (lowercase)
4. If still not found, loop again and check rule 3 (lowercase + vowel masked)
*/

vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
    vector<string> ans;

    for (string q : queries) {
        // Rule 1: exact match
        bool found=false;
        for (string w : wordlist) {
            if (w == q) {ans.push_back(w); found=true; break;}
        }
        if (found) continue;

        // Rule 2: case-insensitive
        string qlow=q; transform(qlow.begin(), qlow.end(), qlow.begin(), ::tolower);
        for (string w : wordlist) {
            string wlow=w; transform(wlow.begin(), wlow.end(), wlow.begin(), ::tolower);
            if (wlow==qlow) {ans.push_back(w); found=true; break;}
        }
        if (found) continue;

        // Rule 3: vowel-masked
        string qmask=maskVowels(qlow);
        for (string w : wordlist) {
            string wlow=w; transform(wlow.begin(), wlow.end(), wlow.begin(), ::tolower);
            if (maskVowels(wlow)==qmask) {ans.push_back(w); found=true; break;}
        }
        if (found) continue;

        // None matched
        ans.push_back("");
    }

    return ans;
}


//Approach-2: HashMap- unordered_map
/*
### Noticing the Pattern
We’re doing the same transformation over and over:
1. Lowercase each word
2. Lowercase + mask vowels
We could compute those once and store them in a map.

#️## Preprocess → The 3 Maps

During preprocessing:
1. exactSet = store all words as-is
2. caseInsensitive = map lowercase → first word with that lowercase
3.vowelMask = map masked(lowercase) → first word with that masked form

Then for each query we:
1. Check exactSet
2. Check caseInsensitive[lowercase(query)]
3. Check vowelMask[maskVowels(lowercase(query))]

Each is O(1) on average.

*/

class Solution {
public:
    string maskVowels(string s) {
        for (char &c : s)
            if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u') c='*';
        return s;
    }

    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<string> exact(wordlist.begin(), wordlist.end());
        unordered_map<string,string> caseInsensitive;
        unordered_map<string,string> vowelMask;

        // build maps
        for (string w : wordlist) {
            string low=w; transform(low.begin(), low.end(), low.begin(), ::tolower);
            if (!caseInsensitive.count(low)) caseInsensitive[low]=w;
            string masked=maskVowels(low);
            if (!vowelMask.count(masked)) vowelMask[masked]=w;
        }

        // answer queries
        vector<string> ans;
        for (string q : queries) {
            if (exact.count(q)) {ans.push_back(q); continue;}
            string low=q; transform(low.begin(), low.end(), low.begin(), ::tolower);
            if (caseInsensitive.count(low)) {ans.push_back(caseInsensitive[low]); continue;}
            string masked=maskVowels(low);
            if (vowelMask.count(masked)) {ans.push_back(vowelMask[masked]); continue;}
            ans.push_back("");
        }
        return ans;
    }
};


// Complexity now:
// Preprocessing O(n * L)
// Each query O(L) (lowercase + mask)
// So total O((n+m) * L)
