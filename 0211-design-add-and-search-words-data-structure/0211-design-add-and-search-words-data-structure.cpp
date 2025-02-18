class WordDictionary {
private:
    unordered_set<string> hashSet;
public:
    WordDictionary() {
        hashSet = unordered_set<string>();
    }
    
    void addWord(string word) {
        hashSet.insert(word);

        for (int i = 0; i < word.size(); i++) {
            char tmp_i = word[i];
            word[i] = '.';

            hashSet.insert(word);

            word[i] = tmp_i;
        }
    }
    
    bool search(string word) {
        if (hashSet.find(word) != hashSet.end())
            return true;

        for (int i = 0; i < word.size(); i++) {
            if (word[i] == '.') {
                for (int c = 0; c < 26; c++) {
                    word[i] = (char)('a' + c);
                    if (hashSet.find(word) != hashSet.end())
                        return true;
                }
                word[i] = '.';
            }
        }
        return false;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */