class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<int> dp(prices.size()+1, 0);

        for (int i = 1; i < prices.size(); i++) {
            dp[i+1] = dp[i];
            for (int j = 0; j < i; j++) {
                dp[i+1] = max(dp[i+1], prices[i] - prices[j] + (j > 0 ? dp[j-1]:0));
            }
        }

        return dp[prices.size()];
    }
};