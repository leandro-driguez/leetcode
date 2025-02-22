class DSU {
private:
    vector<int> root;
    vector<int> rank;
public:
    int N;

    DSU(int n) {
        N = n;

        rank = vector<int>(n, 1);
        root = vector<int>(n, 0);

        for (int i = 0; i < n; i++) {
            root[i] = i;
        }
    }

    int Find(int x) {
        if (root[x] == x)
            return x;
        return root[x] = Find(root[x]);
    }

    void Union(int x, int y) {
        int rootX = Find(x);
        int rootY = Find(y);

        if (rootX != rootY) {
            if (rank[rootX] == rank[rootY])
                rank[rootX]++;
            if (rank[rootX] > rank[rootY])
                root[rootY] = rootX;
            else 
                root[rootX] = rootY;
            N--;
        }
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        auto dsu = DSU(isConnected.size());

        for (int i = 0; i < isConnected.size(); i++) {
            for (int j = i+1; j < isConnected.size(); j++) {
                if (isConnected[i][j])
                    dsu.Union(i, j);
            }
        }

        return dsu.N;
    }
};