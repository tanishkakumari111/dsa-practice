#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        // Sort meetings by time
        sort(meetings.begin(), meetings.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[2] < b[2];
             });

        vector<bool> knows(n, false);
        knows[0] = true;
        knows[firstPerson] = true;

        int i = 0;
        int m = meetings.size();

        while (i < m) {
            int time = meetings[i][2];

            // Graph for current time
            unordered_map<int, vector<int>> graph;
            unordered_set<int> people;

            // Collect all meetings at this time
            while (i < m && meetings[i][2] == time) {
                int x = meetings[i][0];
                int y = meetings[i][1];
                graph[x].push_back(y);
                graph[y].push_back(x);
                people.insert(x);
                people.insert(y);
                i++;
            }

            // BFS starting from people who already know the secret
            queue<int> q;
            unordered_set<int> visited;

            for (int p : people) {
                if (knows[p]) {
                    q.push(p);
                    visited.insert(p);
                }
            }

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : graph[u]) {
                    if (!visited.count(v)) {
                        visited.insert(v);
                        q.push(v);
                    }
                }
            }

            // Mark all reachable people as knowing the secret
            for (int p : visited) {
                knows[p] = true;
            }
        }

        // Collect result
        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (knows[i]) result.push_back(i);
        }

        return result;
    }
};
