class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        int numPairs = 0;
        unordered_map<int,int> hashMap;

        for (int i = 0; i < time.size(); i++) {
            if (hashMap.find((60 - time[i]%60) % 60) != hashMap.end())
                numPairs += hashMap[(60 - time[i]%60) % 60];
            hashMap[time[i]%60]++;
        }

        return numPairs;
    }
};