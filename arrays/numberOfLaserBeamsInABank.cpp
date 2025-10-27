class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int prev = 0; // devices in previous non-empty row
        int result = 0;

        for (auto& row : bank) {
            int devices = count(row.begin(), row.end(), '1');
            if (devices == 0) continue; // skip empty rows

            result += prev * devices;
            prev = devices; // update previous for next non-empty row
        }

        return result;
    }
};
