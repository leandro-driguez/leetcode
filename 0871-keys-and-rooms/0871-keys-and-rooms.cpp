class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        queue<int> q;
        q.push(0);

        int amountOfVisitedRooms = rooms.size();
        vector<bool> visited(rooms.size(), false);
        while (!q.empty()) {
            int room = q.front();
            q.pop();

            if (visited[room])
                continue;
            visited[room] = true;
            amountOfVisitedRooms--;

            for (int r: rooms[room]) {
                if (!visited[r])
                    q.push(r);
            }
        }

        return amountOfVisitedRooms == 0;
    }
};