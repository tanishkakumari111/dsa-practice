class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";

        string ans;

        // Handle sign
        if ((numerator < 0) ^ (denominator < 0))
            ans += "-";

        // Convert to long long to avoid overflow
        long long num = llabs((long long)numerator);
        long long den = llabs((long long)denominator);

        // Integer part
        long long integerPart = num / den;
        ans += to_string(integerPart);

        long long rem = num % den;
        if (rem == 0) return ans; // no fractional part

        ans += ".";

        // fractional part
        unordered_map<long long, int> seen; // remainder -> position in res

        while (rem != 0) {
            if (seen.count(rem)) {
                // Insert '(' at the index where this remainder first appeared
                ans.insert(seen[rem], "(");
                ans += ")";
                break;
            }

            seen[rem] = ans.size();
            rem *= 10;
            long long digit = rem / den;
            ans += to_string(digit);
            rem %= den;
        }

        return ans;
    }
};
