class Solution {
private:
    bool dfsVisit(vector<vector<int>>& graph, int u, vector<int>& visited) {
        // there is a cycle
        if (visited[u] == 1) {
            visited[u] = -1;
            return false;
        }
        // find a non-safe node
        if (visited[u] == -1)
            return false;
        // find a safe node
        if (visited[u] == 2)
            return true;
        visited[u] = 1;

        for (int v: graph[u]) {
            if (!dfsVisit(graph, v, visited)) {
                visited[u] = -1;
                return false;
            }
        }

        visited[u] = 2;
        return true;
    }
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> visited(n, 0);
        vector<int> safeStates;

        for (int i = 0; i < n; i++) {
            if (dfsVisit(graph, i, visited))
                safeStates.push_back(i);
        }

        return safeStates;
    }
};