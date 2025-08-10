class Solution {
public:
    int connectSticks(vector<int>& sticks) {
        priority_queue<int> heap;
        for (int x: sticks) {
            heap.push(-x);
        }

        int costOfConnect = 0;
        while (heap.size() > 1) {
            int x = -heap.top();
            heap.pop();
            int y = -heap.top();
            heap.pop();

            costOfConnect += x+y;
            heap.push(-x-y);
        }
        return costOfConnect;
    }
};