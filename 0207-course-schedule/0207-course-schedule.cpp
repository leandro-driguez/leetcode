class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses, vector<int>());
        vector<int> degree(numCourses);
        for (int i = 0, crs, preq; i < prerequisites.size(); i++) {
            crs  = prerequisites[i][0];
            preq = prerequisites[i][1];
            graph[preq].push_back(crs);
            degree[crs]++;
        }

        stack<int> coursesReady;
        for (int i = 0; i < numCourses; i++) {
            if (degree[i] == 0)
                coursesReady.push(i);
        }

        while (!coursesReady.empty()) {
            int preq = coursesReady.top();
            coursesReady.pop();
            numCourses--;

            for (int crs: graph[preq]) {
                degree[crs]--;
                if (degree[crs] == 0)
                    coursesReady.push(crs);
            }
        }

        return numCourses == 0;
    }
};