class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<int> accMin(prices.size(), 10e4);
        for (int i = 0; i < prices.size(); i++) {
            if (i != 0) {
                accMin[i] = min(accMin[i-1], prices[i]);
            }
            else {
                accMin[i] = prices[i];
            }
        }

        int _maxProfit = 0;
        for (int i = prices.size()-1; i > 0; i--) {
            _maxProfit = max(_maxProfit, prices[i] - accMin[i-1]);
        }
        return _maxProfit;
    }
};