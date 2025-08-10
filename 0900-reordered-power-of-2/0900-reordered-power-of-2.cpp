class Solution {
private:
    string convertToSortedString(int n) {
        string s = to_string(n);
        sort(s.begin(), s.end());
        return s;
    }
public:
    bool reorderedPowerOf2(int n) {
        string n_str = convertToSortedString(n);
        
        for (int i = 0; i < 31; i++) {
            int power = 1<<i;
            if (convertToSortedString(power) == n_str)
                return true;
        }

        return false;
    }
};