/*
🔧 Data structure / design choice
A few candidate designs:
1. Full 2D array (matrix) of size [rows][26]
Pros: direct access, very fast.
Cons: uses memory for all cells even unused ones, but 26,000 isn’t huge; still acceptable given constraints.

2. Sparse representation — hash map / unordered_map storing only those cells that are explicitly set (non-zero). If unset, default is 0.
Pros: less memory if most cells stay 0.
Cons: extra overhead on lookup (hashing string → key). But since constraints are moderate, overhead is acceptable.

*** Given constraints, both approaches can pass. Sparse is simpler in code, perhaps a little slower per lookup due to map operations, but within limit for 10^4 operations. ***
*/


#include <bits/stdc++.h>
using namespace std;

class Spreadsheet {
private:
    // maps (rowIndex*26 + colIndex) -> value
    unordered_map<int,int> mp;
    int nRows;

    inline int encode(const string &cell) { 
        // cell like "A1" or "C23"
        // parse col char:
        int col = cell[0] - 'A'; // 0..25
        // parse row (from index 1)
        int row = 0;
        for (int i = 1; i < (int)cell.size(); i++) {    
            row = row*10 + (cell[i]-'0');
        }
        row -= 1; // zero-based
        return row*26 + col;
    }

    inline int tokenValue(const string &token) {     
        if (isdigit(token[0])) {
            return stoi(token);
        } else {
            int k = encode(token);
            auto it = mp.find(k);
            return it == mp.end() ? 0 : it->second;
        }
    }

public:
    Spreadsheet(int rows) { //TC: O(1)    SC: O(K)
        nRows = rows;
        mp.reserve(rows*26/4);
    }

    void setCell(const string &cell, int value) { //TC: O(1)    SC: O(K)
        int k = encode(cell);
        mp[k] = value;
    }

    void resetCell(const string &cell) { //TC: O(1)     SC: O(K)
        int k = encode(cell);
        mp.erase(k);
    }

    int getValue(const string &formula) { //TC: O(1)       SC: O(K)
        // "=X+Y"
        int plusPos = 1;
        while (plusPos < (int)formula.size() && formula[plusPos] != '+')
            plusPos++;

        string op1 = formula.substr(1, plusPos-1);
        string op2 = formula.substr(plusPos+1);

        return tokenValue(op1) + tokenValue(op2);
    }
};


/*
⚠️ Possible pitfalls / things to watch:
1. When parsing the cell string (like "A12"), you need to split off the column part ("A") and row part ("12") if you want to validate or use 2D array. With sparse map you can treat the whole cell string as key.
2. Leading zeros (though probably none in input).
3. Big integer literals in formulas (but bounded by 10^5, so safe to parse into int).
4.Assignment vs erase: resetting cell should probably remove from map so future lookups treat it as default‐0 and map size is smaller. 
*/


/*
. size() → size_t (unsigned)
. Loop variable i → int (signed)

(int) cast makes types match, avoids compiler warnings and possible bugs.

If you instead declared i as size_t i = 1;, you wouldn’t need the cast.
It’s purely a type-safety / warning-avoidance measure, not a functional requirement.
*/

/*
How the author got it:  mp.reserve(rows*26/4);
The spreadsheet has at most rows * 26 cells (26 columns, rows rows).
In practice, most of them will remain 0 and never be stored in the map.
If you expect to only fill a fraction of the cells (say 25 % of them), you can pre-allocate about rows * 26 / 4 buckets.
So *26/4 = 26 columns × 25 % usage estimate.
  */
