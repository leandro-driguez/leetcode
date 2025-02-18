class Solution {
public:
    int trap(vector<int>& height) {
        deque<int> s;

        int amountWater = 0;
        for (int i = 0; i < height.size(); i++) {
            if (!s.empty()) {
                if (s.front() <= height[i]) {
                    while (!s.empty()) {
                        amountWater += s.front()-s.back();
                        s.pop_back();
                    }
                }
                else if (s.back() < height[i]) {
                    int refill = 0;
                    while (!s.empty() && s.back() < height[i]) {
                        amountWater += height[i]-s.back();
                        s.pop_back();
                        refill++;
                    }
                    for (int j = 0; j < refill; j++) {
                        s.push_back(height[i]);
                    }
                }
            }
            s.push_back(height[i]);
        }

        return amountWater;
    }
};