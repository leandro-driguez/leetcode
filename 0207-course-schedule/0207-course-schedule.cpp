class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> reverseGraph(numCourses);
        vector<int> indegree(numCourses, 0);
        for (int i = 0, pre, crs; i < prerequisites.size(); i++) {
            crs = prerequisites[i][0];
            pre = prerequisites[i][1];
            reverseGraph[pre].push_back(crs);
            indegree[crs]++;
        }

        queue<int> noPrereq;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0)
                noPrereq.push(i);
        }
        if (noPrereq.empty())
            return false;

        while (!noPrereq.empty()) {
            int course = noPrereq.front();
            noPrereq.pop();

            for (int nextCourse: reverseGraph[course]) {
                indegree[nextCourse]--;
                if (indegree[nextCourse] == 0)
                    noPrereq.push(nextCourse);
                if (indegree[nextCourse] < 0)
                    return false;
            }
        }

        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] > 0)
                return false;
        }

        return true;
    }
};