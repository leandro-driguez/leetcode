class Solution {
private:
    int auxMinOp(vector<int>& nums, int i) {
        int commonGcdReverse = nums[i];
        int j = i-1;
        
        for (; j >= 0; j--) {
            commonGcdReverse = gcd(commonGcdReverse, nums[j]);
            if (commonGcdReverse == 1)
                break;
        }

        return i-j;
    }

    int count1(vector<int>& nums) {
        int amount = 0;
        for(auto x: nums) {
            if (x == 1)
                amount++;
        }
        return amount;
    }
public:
    int minOperations(vector<int>& nums) {
        int commonGcd = nums[0];
        int n = nums.size();
        int minSubarr = INT_MAX;

        if (nums[0] == 1)
            return n-count1(nums);

        int i = 1;
        for (; i < n; i++) {
            if (nums[i] == 1)
                return n-count1(nums);
            
            commonGcd = gcd(commonGcd, nums[i]);
        
            if (commonGcd == 1) {
                minSubarr = min(minSubarr, auxMinOp(nums, i));
                commonGcd = nums[i];
            }
        }

        return minSubarr == INT_MAX? -1: minSubarr + n-1;
    }
};