struct OfflineUser {
    int returnTimestamp;
    int userId;
    bool operator>(const OfflineUser& other) const {
        return returnTimestamp > other.returnTimestamp;
    }
};

class Solution {
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        vector<int> ans(numberOfUsers, 0);
        vector<int> online(numberOfUsers, 1); // 1 = online, 0 = offline
        priority_queue<OfflineUser, vector<OfflineUser>, greater<OfflineUser>> offlineQ;
        int allMentionsCount = 0;

        // Sort events by (timestamp, eventType) where eventType reversed so MESSAGE processed before OFFLINE
        sort(events.begin(), events.end(), [](const vector<string>& a, const vector<string>& b){
            int ta = stoi(a[1]);
            int tb = stoi(b[1]);
            if (ta != tb) return ta < tb;
            // To break ties, put events with lexicographically larger event type first (same idea as -eventType)
            return a[0] > b[0];
        });

        for (const auto &ev : events) {
            const string &eventType = ev[0];
            int timestamp = stoi(ev[1]);

            // Bring users back online if their offline window has ended
            while (!offlineQ.empty() && offlineQ.top().returnTimestamp <= timestamp) {
                online[offlineQ.top().userId] = 1;
                offlineQ.pop();
            }

            if (eventType == "MESSAGE") {
                const string &content = ev[2];

                if (content == "ALL") {
                    // Lazy: count this as an ALL mention; add to everyone at the end
                    ++allMentionsCount;
                } else if (content == "HERE") {
                    // Mention all currently online users
                    for (int u = 0; u < numberOfUsers; ++u) {
                        if (online[u]) ++ans[u];
                    }
                } else {
                    // content is a space-separated list of mention tokens (e.g. "U0 U3" or "@U0 U2")
                    vector<int> ids = parseMentionedIds(content);
                    for (int id : ids) {
                        if (0 <= id && id < numberOfUsers) ++ans[id];
                    }
                }
            } else if (eventType == "OFFLINE") {
                // ev[2] is user id (string). Convert and mark offline, schedule return at timestamp + 60.
                int userId = stoi(ev[2]);
                if (0 <= userId && userId < numberOfUsers) {
                    online[userId] = 0;
                    offlineQ.push({timestamp + 60, userId});
                }
            }
            // Other event types (if any) are ignored
        }

        // Apply lazy ALL mentions to every user
        if (allMentionsCount) {
            for (int u = 0; u < numberOfUsers; ++u) ans[u] += allMentionsCount;
        }

        return ans;
    }

private:
    // Robust parser: extracts integer ids from tokens separated by spaces.
    // Each token may contain non-digit prefixes; we collect contiguous digits and parse them.
    vector<int> parseMentionedIds(const string &s) {
        vector<int> ids;
        int n = s.size();
        int i = 0;
        while (i < n) {
            // skip spaces
            while (i < n && isspace((unsigned char)s[i])) ++i;
            if (i >= n) break;

            // read token until next space
            int j = i;
            while (j < n && !isspace((unsigned char)s[j])) ++j;
            // extract digits from s[i..j-1]
            long long val = 0;
            bool foundDigit = false;
            for (int k = i; k < j; ++k) {
                if (isdigit((unsigned char)s[k])) {
                    foundDigit = true;
                    val = val * 10 + (s[k] - '0');
                    if (val > INT_MAX) break;
                }
            }
            if (foundDigit) ids.push_back(static_cast<int>(val));
            i = j;
        }
        return ids;
    }
};
