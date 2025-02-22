class Solution {
public:
    int lengthOfLastWord(string s) {
        string currWord = "";
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                while (i < s.size() && s[i] == ' ') {i++;}
                i--;
            }
            else {
                currWord = "";
                while (i < s.size() && s[i] != ' ') { currWord += string(1, s[i++]); }
                i--;
            }
        }
        return currWord.size();
    }
};