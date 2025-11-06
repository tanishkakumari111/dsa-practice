#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p;
    DSU(int n=0): n(n), p(n+1) { for(int i=0;i<=n;i++) p[i]=i; }
    int find(int x){ return p[x]==x? x : p[x]=find(p[x]); }
    void unite(int a,int b){ 
        a = find(a); b = find(b);
        if(a!=b) p[a]=b;
    }
};

class Solution {
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        DSU dsu(c);
        for (auto &e : connections) dsu.unite(e[0], e[1]);

        // group nodes by root; nodes are added in increasing order -> groups are sorted ascending
        vector<vector<int>> groups(c+1);
        for (int i = 1; i <= c; ++i) {
            int r = dsu.find(i);
            groups[r].push_back(i);
        }

        // pointer for each root to lazily skip closed nodes
        vector<int> ptr(c+1, 0);
        vector<char> online(c+1, 1); // 1 = online, 0 = closed

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int type = q[0], x = q[1];
            if (type == 2) {
                // close station x
                online[x] = 0;
            } else {
                // type == 1: check at station x
                if (online[x]) {
                    // if x is online, it answers the check
                    ans.push_back(x);
                    continue;
                }
                // otherwise find smallest online station in the same component
                int root = dsu.find(x);
                auto &vec = groups[root];
                int &i = ptr[root];
                // advance pointer until we find an online station or exhaust
                while (i < (int)vec.size() && !online[vec[i]]) ++i;
                if (i < (int)vec.size()) ans.push_back(vec[i]);
                else ans.push_back(-1);
            }
        }
        return ans;
    }
};
