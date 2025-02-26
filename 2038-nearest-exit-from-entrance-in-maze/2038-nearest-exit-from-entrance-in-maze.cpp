class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        queue<pair<int, pair<int,int>>> q;
        q.push({0, {entrance[0], entrance[1]}});
        
        maze[entrance[0]][entrance[1]] = '0';

        int vR[] = {1, 0, -1, 0};
        int vC[] = {0, 1, 0, -1};

        while (!q.empty()) {
            auto cell = q.front();
            q.pop();
            
            if (maze[cell.second.first][cell.second.second] == '.')
                maze[cell.second.first][cell.second.second] = 'x';
            else if (maze[cell.second.first][cell.second.second] == 'x')
                continue;

            if ((cell.second.first == 0 || cell.second.second == 0 || cell.second.first+1 == maze.size() || cell.second.second+1 == maze[0].size()) && maze[cell.second.first][cell.second.second] != '0')
                return cell.first;

            for (int d = 0, r, c; d < 4; d++) {
                r = cell.second.first + vR[d];
                c = cell.second.second + vC[d];

                if (r < 0 || c < 0 || r >= maze.size() || c >= maze[0].size())
                    continue;
                if (maze[r][c] == '.')
                    q.push({cell.first+1, {r,c}});
            }
        }

        return -1;
    }
};

// ["+",".","+","+","+","+","+"]
// ["+",".","+",".",".",".","+"]
// ["+",".","+",".","+",".","+"]
// ["+",".",".",".","+",".","+"]
// ["+","+","+","+","+",".","+"]
