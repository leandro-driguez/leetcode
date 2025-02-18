class Solution {
private:
    vector<string> split(const string& s) {
        // This regex has:
        //   - a capturing group for any arithmetic operator: +, -, *, or /
        //   - or matches one or more whitespace characters (\s+)
        // The pattern: "([+\\-*/])|\\s+"
        regex re("([+\\-*/])|\\s+");

        // sregex_token_iterator with indices {-1, 1} returns:
        //  - Index -1: parts of the string that did not match the regex (non-delimiter parts)
        //  - Index 1: the captured arithmetic operators (when matched)
        sregex_token_iterator it(s.begin(), s.end(), re, {-1, 1});
        sregex_token_iterator end;

        vector<string> tokens;
        for (; it != end; ++it) {
            string token = it->str();
            // Skip empty tokens (they result from matches on whitespace)
            if (!token.empty())
                tokens.push_back(token);
        }
        return tokens;
    }

public:
    int calculate(string s) {
        vector<string> tokens = split(s);
        int result = 0, lastNumber = -1;
        
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-") {
                result += lastNumber;

                if (tokens[i] == "-") {   
                    lastNumber = -stoi(tokens[++i]);
                }
            }
            else if (tokens[i] == "*") {
                lastNumber *= stoi(tokens[++i]);
            }
            else if (tokens[i] == "/") {
                lastNumber /= stoi(tokens[++i]); 
            }
            else {
                lastNumber = stoi(tokens[i]);
            }
        }
        return result + lastNumber;
    }
};