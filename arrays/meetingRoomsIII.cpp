class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // Sort meetings by start time
        sort(meetings.begin(), meetings.end());

        // Min-heap of available rooms
        priority_queue<int, vector<int>, greater<int>> freeRooms;
        for (int i = 0; i < n; i++) {
            freeRooms.push(i);
        }

        // Min-heap of busy rooms: (endTime, roomIndex)
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<pair<long long, int>>> busyRooms;

        vector<int> count(n, 0);

        for (auto& m : meetings) {
            long long start = m[0];
            long long end = m[1];
            long long duration = end - start;

            // Free rooms that have finished
            while (!busyRooms.empty() && busyRooms.top().first <= start) {
                freeRooms.push(busyRooms.top().second);
                busyRooms.pop();
            }

            if (!freeRooms.empty()) {
                // Assign to free room
                int room = freeRooms.top();
                freeRooms.pop();
                busyRooms.push({end, room});
                count[room]++;
            } else {
                // Delay meeting
                auto [availableTime, room] = busyRooms.top();
                busyRooms.pop();
                busyRooms.push({availableTime + duration, room});
                count[room]++;
            }
        }

        // Find room with max meetings
        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (count[i] > count[ans]) {
                ans = i;
            }
        }

        return ans;
    }
};
