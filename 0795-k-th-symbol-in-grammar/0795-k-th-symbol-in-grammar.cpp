class Solution {
public:
    int aux(int n, int k) {
        if (n == 0)
            return 0;
        int val = aux(n-1, k / 2);
        if (k % 2 == 0)
            return val;
        else
            return !val;
    }
    int kthGrammar(int n, int k) {
        return aux(n-1, k-1);
    }
};