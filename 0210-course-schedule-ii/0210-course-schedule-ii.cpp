class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses);
        for (int i = 0, from, to; i < prerequisites.size(); i++) {
            from = prerequisites[i][1];
            to   = prerequisites[i][0];
            indegree[to]++;
            graph[from].push_back(to);
        }

        queue<int> q;
        for (int i = 0; i < indegree.size(); i++) {
            if (indegree[i] == 0)
                q.push(i);
        }

        vector<int> topSort;
        while (!q.empty()) {
            int prereq = q.front();
            q.pop();
            topSort.push_back(prereq);

            for (int course: graph[prereq]) {
                indegree[course]--;
                if (indegree[course] == 0)
                    q.push(course);
            }
        }

        if (topSort.size() != numCourses)
            return {};
        return topSort;
    }
};