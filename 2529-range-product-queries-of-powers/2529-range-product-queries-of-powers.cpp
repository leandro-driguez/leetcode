class Solution {
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        long long MOD1 = 1e9+7;
        int MOD2 = 50;
        
        vector<int> exps;
        while (n > 0) {
            int maxPow = (int)floor(log2(n));
            exps.push_back(maxPow);
            n -= pow(2, maxPow);
        }
        exps.push_back(0);
        
        for(int i=exps.size()-2; i >= 0; i--){
            exps[i] += exps[i+1];
        }

        vector<int> ans;
        for(int i = 0, l, r, exp; i<queries.size();i++) {
            l = queries[i][0];
            r = queries[i][1]+1;
            exp = exps[exps.size()-1-r]-exps[exps.size()-1-l];
            long long res = 1;
            while (exp > MOD2) {
                res = (res * ((long long)pow((long long)2, (long long)MOD2) % MOD1)) % MOD1;
                exp -= MOD2;
            }

            res = (res * ((long long)pow((long long)2, (long long)exp) % MOD1)) % MOD1;
            ans.push_back((int)res);
        }
        
        return ans;
    }
};