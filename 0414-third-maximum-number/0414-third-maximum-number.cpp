class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long long maxx1=(long long)INT_MIN-1, maxx2=(long long)INT_MIN-1, maxx3=(long long)INT_MIN-1;
        for (int i=0; i<nums.size();i++){
            if (nums[i] > maxx1) {
                maxx3 = maxx2;
                maxx2 = maxx1;
                maxx1 = nums[i];
            }
            else if (nums[i] != maxx1) {
                if (nums[i] > maxx2) {
                    maxx3 = maxx2;
                    maxx2 = nums[i];
                }
                else if (nums[i] != maxx2) {
                    if (nums[i] > maxx3)
                        maxx3 = nums[i];
                }
            }
        }
        return maxx3 != (long long)INT_MIN-1? maxx3 : maxx1;
    }
};