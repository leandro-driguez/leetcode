class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> lines;

        for (int i = 0, width; i < (int)words.size();) {
            vector<string> line = {words[i++]};
            width = maxWidth - line[0].size();

            if ((i < (int)words.size() && width - 1 < (int)words[i].size()) || i == (int)words.size()) {
                string spaces = "";
                for (int j = 0; j < width; j++) spaces += " ";
                line.push_back(spaces);
            }
            else {
                for (; i < (int)words.size() && width - 1 >= (int)words[i].size(); i++) {
                    line.push_back(" ");
                    line.push_back(words[i]);
                    width -= words[i].size()+1;
                }

                if (width > 0) {
                    // last line
                    if (i == (int)words.size()) {
                        string spaces = "";
                        for (int j = 0; j < width; j++) spaces += " ";
                        line.push_back(spaces);
                    }
                    // other line
                    else {
                        int perSpace    = width / ((int)line.size()/2);
                        int firstSpaces = width % ((int)line.size()/2);

                        for (int j = 1; j < (int)line.size(); ) {
                            for (int k = 0; k < perSpace; k++) line[j] += " ";
                            if (j / 2 < firstSpaces)
                                line[j] += " ";
                            j += 2;
                        }
                    }
                }
            }

            string fullLine = "";
            for (string w: line) fullLine += w;

            lines.push_back(fullLine);
        }

        return lines;
    }
};