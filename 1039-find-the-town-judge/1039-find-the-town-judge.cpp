class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<vector<int>> inEdges(n), outEdges(n);
        
        for (int i = 0; i < trust.size(); i++) {
            inEdges[trust[i][1]-1].push_back(trust[i][0]-1);
            outEdges[trust[i][0]-1].push_back(trust[i][1]-1);
        }

        for (int i = 0; i < n; i++) {
            if (inEdges[i].size() == n-1 && outEdges[i].size() == 0)
                return i+1;
        }

        return -1;
    }
};