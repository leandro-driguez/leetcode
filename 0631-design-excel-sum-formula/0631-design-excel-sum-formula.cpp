class Excel {
private:
    vector<vector<int>> matrix;
    unordered_map<int,unordered_map<int,vector<pair<int,int>>*>> unUpdated;
    unordered_map<int,unordered_map<int,vector<pair<int,int>>*>> unUpdatedReverse;
    unordered_map<int,unordered_map<int,vector<string>*>> sums;

public:
    Excel(int height, char width) {
        matrix = vector<vector<int>>(height, vector<int>(width-'A'+1, 0));
    }
    
    void set(int row, char column, int val) {
        matrix[row-1][column-'A'] = val;
        if (unUpdated[row-1][column-'A'] != nullptr) {
            for(auto pairs: *unUpdated[row-1][column-'A']){
                int x = pairs.first;
                int y = pairs.second;
                matrix[x][y] = -1001;
            }
        }
        if (unUpdatedReverse[row-1][column-'A'] != nullptr) {
            for(auto pairs: *unUpdatedReverse[row-1][column-'A']){
                int x = pairs.first;
                int y = pairs.second;
                
                auto it = find(unUpdated[x][y]->begin(), unUpdated[x][y]->end(), make_pair(row-1, column-'A'));
                if (it != unUpdated[x][y]->end())
                    unUpdated[x][y]->erase(it);
            }
            unUpdatedReverse[row-1][column-'A'] = nullptr;
        }
    }
    
    int get(int row, char column) {
        // if (row==1 && column=='C'){
        // for(auto row: matrix) {
        //     for(int x: row) {
        //         cout<<x<<" ";
        //     }
        //     cout<<endl;
        // }
        // }
        if (row==1 && column=='B'){
        for(auto row: matrix) {
            for(int x: row) {
                cout<<x<<" ";
            }
            cout<<endl;
        }
        cout<<endl<<endl;
        }
        
        if (matrix[row-1][column-'A'] == -1001) {
            int totalValue = 0;
            vector<string> numbers = *sums[row-1][column-'A'];
            
            for (int  i = 0; i<numbers.size(); i++) {
                if (numbers[i].size() > 3) {
                    int j = 0;
                    int col1 = numbers[i][j++] - 'A';
                    int row1 = numbers[i][j++] - '0';
                    if (numbers[i][j] != ':') {
                        row1 *= 10;
                        row1 += numbers[i][j++] - '0';
                    }
                    j++;

                    int col2 = numbers[i][j++] - 'A';
                    int row2 = numbers[i][j++] - '0';
                    if (j < numbers[i].size()) {
                        row2 *= 10;
                        row2 += numbers[i][j] - '0';
                    }

                    for (int k = row1; k <= row2; k++) {
                        for (int h = col1; h <= col2; h++) {
                            totalValue += get(k, (char)(h+'A'));
                        }
                    }
                }
                else {
                    int row = numbers[i][1] - '0';
                    
                    if (numbers[i].size() == 3) {
                        row *= 10;
                        row += numbers[i][2] - '0';
                    }

                    totalValue += get(row, numbers[i][0]);
                }
            }
            
            matrix[row-1][column-'A'] = totalValue;
            if (unUpdated[row-1][column-'A'] != nullptr) {
            for(auto pairs: *unUpdated[row-1][column-'A']){
                int x = pairs.first;
                int y = pairs.second;
                matrix[x][y] = -1001;
            }
        }
        }
        return matrix[row-1][column-'A'];
    }
    
    int sum(int row, char column, vector<string> numbers) {
        matrix[row-1][column-'A'] = -1001;
        sums[row-1][column-'A'] = new vector<string>(numbers);

        if (unUpdatedReverse[row-1][column-'A'] != nullptr) {
            for(auto pairs: *unUpdatedReverse[row-1][column-'A']){
                int x = pairs.first;
                int y = pairs.second;
                
                auto it = find(unUpdated[x][y]->begin(), unUpdated[x][y]->end(), make_pair(row-1, column-'A'));
                if (it != unUpdated[x][y]->end())
                    unUpdated[x][y]->erase(it);
            }
            unUpdatedReverse[row-1][column-'A'] = nullptr;
        }

        for (int  i = 0; i<numbers.size(); i++) {
            if (numbers[i].size() > 3) {
                int j = 0;
                int col1 = numbers[i][j++] - 'A';
                int row1 = numbers[i][j++] - '0';
                if (numbers[i][j] != ':') {
                    row1 *= 10;
                    row1 += numbers[i][j++] - '0';
                }
                j++;

                int col2 = numbers[i][j++] - 'A';
                int row2 = numbers[i][j++] - '0';
                if (j < numbers[i].size()) {
                    row2 *= 10;
                    row2 += numbers[i][j] - '0';
                }

                for (int k = row1; k <= row2; k++) {
                    for (int h = col1; h <= col2; h++) {
                        if (unUpdated[k-1][h] == nullptr) {
                            unUpdated[k-1][h] = new vector<pair<int,int>>();
                        }
                        unUpdated[k-1][h]->push_back({row-1,column-'A'});

                        if (unUpdatedReverse[row-1][column-'A'] == nullptr) {
                            unUpdatedReverse[row-1][column-'A'] = new vector<pair<int,int>>();
                        }
                        unUpdatedReverse[row-1][column-'A']->push_back({k-1, h});
                    }
                }
            }
            else {
                int row1 = numbers[i][1] - '0';
                int col1 = numbers[i][0] - 'A';
                
                if (numbers[i].size() == 3) {
                    row1 *= 10;
                    row1 += numbers[i][2] - '0';
                }

                if (unUpdated[row1-1][col1] == nullptr) {
                    unUpdated[row1-1][col1] = new vector<pair<int,int>>();
                }
                unUpdated[row1-1][col1]->push_back({row-1,column-'A'});

                if (unUpdatedReverse[row-1][column-'A'] == nullptr) {
                    unUpdatedReverse[row-1][column-'A'] = new vector<pair<int,int>>();
                }
                unUpdatedReverse[row-1][column-'A']->push_back({row1-1, col1});
            }
        }

        return get(row, column);
    }
};

/**
 * Your Excel object will be instantiated and called as such:
 * Excel* obj = new Excel(height, width);
 * obj->set(row,column,val);
 * int param_2 = obj->get(row,column);
 * int param_3 = obj->sum(row,column,numbers);
 */