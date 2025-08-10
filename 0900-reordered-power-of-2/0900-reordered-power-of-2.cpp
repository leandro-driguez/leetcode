class Solution {
private:
    string convertToSortedString(int n) {
        vector<int> freq(10, 0);
        while (n > 0) {
            int dig = n % 10;
            n = n / 10;
            freq[dig]++;
        }
        string res = "";
        for (int i = 0; i < 10; i++) {
            if (freq[i] > 0) {
                char c = '0' + i;
                string tmp;
                tmp = c;

                while (freq[i] > 0) {
                    res += tmp;
                    freq[i]--;
                }
            }
        }
        return res;
    }
public:
    bool reorderedPowerOf2(int n) {
        unordered_set<string> hashSet;
        for (int i = 1; i < 1e9;) {
            string s = convertToSortedString(i);
            hashSet.insert(s);
            i *= 2;
        }

        string n_str = convertToSortedString(n);

        return hashSet.find(n_str) != hashSet.end();
    }
};