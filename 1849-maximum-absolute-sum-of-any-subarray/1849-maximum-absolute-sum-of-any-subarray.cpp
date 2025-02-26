class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int maxAbsSum = abs(nums[0]);
        int minn = min(0, nums[0]);
        int maxx = max(0, nums[0]);

        for (int i = 1; i < nums.size(); i++) {
            nums[i] += nums[i-1];
            minn = min(minn, nums[i]);
            maxx = max(maxx, nums[i]);

            maxAbsSum = max(maxAbsSum, abs(nums[i]-maxx));
            maxAbsSum = max(maxAbsSum, abs(nums[i]-minn));            
        }

        return maxAbsSum;
    }
};