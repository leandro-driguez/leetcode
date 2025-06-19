class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        
        int amountPartitions = 0; 
        for (int i = 0, j = 0; i < nums.size();) {
            amountPartitions++;
            while (j < nums.size() && nums[j] - nums[i] <= k) {
                j++;
            }
            i = j;
        }
        return amountPartitions;
    }
};