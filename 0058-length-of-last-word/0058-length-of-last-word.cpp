class Solution {
public:
    int lengthOfLastWord(string s) {
        int ptr1, ptr2;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                while (i < s.size() && s[i] == ' ') {i++;}
                i--;
            }
            else {
                ptr1 = i; ptr2 = i;
                while (i < s.size() && s[i] != ' ') { ptr2=i; i++; }
                i--;
            }
        }
        return ptr2-ptr1+1;
    }
};