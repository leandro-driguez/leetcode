class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> bestSeq;

        for (int i = 0; i < nums.size(); i++) {
            auto it = upper_bound(bestSeq.begin(), bestSeq.end(), nums[i]);
            if (it == bestSeq.end()) {
                if (!bestSeq.empty() && nums[i] == *bestSeq.rbegin())
                    continue;
                bestSeq.push_back(nums[i]);
            }
            else {
                int idx = it - bestSeq.begin();
                if (idx > 0 && nums[i] == bestSeq[idx-1])
                    continue;
                bestSeq[idx] = min(bestSeq[idx], nums[i]);
            }
        }

        return bestSeq.size();
    }
};