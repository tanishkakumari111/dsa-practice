class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        queue<string> q;
        unordered_set<string> visited;
        string smallest = s;
        
        q.push(s);
        visited.insert(s);
        
        while (!q.empty()) {
            string cur = q.front();
            q.pop();
            
            if (cur < smallest) smallest = cur;
            
            // 1. Add operation
            string added = cur;
            for (int i = 1; i < added.size(); i += 2) {
                int digit = (added[i] - '0' + a) % 10;
                added[i] = char('0' + digit);
            }
            if (!visited.count(added)) {
                visited.insert(added);
                q.push(added);
            }
            
            // 2. Rotate operation
            string rotated = cur.substr(cur.size() - b) + cur.substr(0, cur.size() - b);
            if (!visited.count(rotated)) {
                visited.insert(rotated);
                q.push(rotated);
            }
        }
        
        return smallest;
    }
};
