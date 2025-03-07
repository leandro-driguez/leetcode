class Solution {
private:
    void discoverIsland(vector<vector<char>>& grid, int r, int c) {
        queue<pair<int,int>> q;
        q.push({r,c});

        int vR[] = {1, 0, -1, 0};
        int vC[] = {0, 1, 0, -1};
        
        while (!q.empty()) {
            auto cell = q.front();
            q.pop();
            
            if (grid[cell.first][cell.second] == '-')
                continue;
            grid[cell.first][cell.second] = '-';

            for (int d = 0, i, j; d < 4; d++) {
                i = cell.first + vR[d];
                j = cell.second + vC[d];

                if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size())
                    continue;
                
                if (grid[i][j] == '1') {
                    q.push({i,j});
                }
            }
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int amountIslands = 0;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    amountIslands++;
                    discoverIsland(grid, i, j);
                }
            }
        }

        return amountIslands;
    }
};