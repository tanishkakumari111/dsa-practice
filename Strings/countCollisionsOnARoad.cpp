class Solution {
public:
    int countCollisions(string s) {
        int n = s.size();
        int i = 0, j = n - 1;

        // Ignore leading L
        while (i < n && s[i] == 'L') i++;

        // Ignore trailing R
        while (j >= 0 && s[j] == 'R') j--;

        int collisions = 0;
        for (int k = i; k <= j; ++k) {
            if (s[k] != 'S')
                collisions++;
        }
        return collisions;
    }
};
