class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int prevSubarray1 = -1;
        int currentSubarray1 = 0;
        int findMax = 0;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                findMax = max(findMax, 1 + currentSubarray1);
                if (i + 1 < nums.size()) {
                    if (nums[i+1] == 0) {
                        prevSubarray1 = -1;
                        currentSubarray1 = 0;
                    }
                    else {
                        prevSubarray1 = currentSubarray1;
                        currentSubarray1 = 0;
                    }
                }
            }
            else {
                currentSubarray1++;
                findMax = max(findMax, prevSubarray1 + 1 + currentSubarray1);
            }
        }

        return findMax;
    }
};