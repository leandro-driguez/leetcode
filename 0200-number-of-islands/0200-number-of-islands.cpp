class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        
        int vX[4] = {0, 1, 0, -1};
        int vY[4] = {-1, 0, 1, 0};

        queue<pair<int,int>> q;

        int amountIslands = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    amountIslands++;

                    grid[i][j] = '0';
                    q.push({i,j});

                    while (!q.empty()) {
                        auto cell = q.front();
                        q.pop();

                        for (int d = 0, r, c; d < 4; d++) {
                            r = cell.first + vY[d];
                            c = cell.second + vX[d];

                            if (r >= 0 && r < n && c >= 0 && c < m && grid[r][c] == '1') {
                                grid[r][c] = '0';
                                q.push({r,c});
                            }
                        }
                    }
                }
            }
        }
        return amountIslands;
    }
};