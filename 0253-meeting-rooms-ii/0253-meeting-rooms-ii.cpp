class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), 
        [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        priority_queue<int> rooms;
        int minMeetRooms = 0;
        for (int i = 0; i < intervals.size(); i++) {
            if (!rooms.empty()) {
                if (intervals[i][0] < -rooms.top())
                    rooms.push(-intervals[i][1]);
                else {
                    while (!rooms.empty() && intervals[i][0] >= -rooms.top())
                        rooms.pop();
                    rooms.push(-intervals[i][1]);
                }
            }
            else {
                rooms.push(-intervals[i][1]);
            }
            minMeetRooms = max(minMeetRooms, (int)rooms.size());
        }
        return minMeetRooms;
    }
};