class Cell {
public:
    vector<pair<int,int>>* dependencies;
    vector<pair<int,int>>* commitments;
    int Value;

    Cell(vector<pair<int,int>>* dependencies) {
        this->dependencies = dependencies;
        commitments = new vector<pair<int,int>>();
        Value = 0;
    }

    void addCommitment(pair<int,int> cell) {
        this->commitments->push_back(cell);
    }

    void removeCommitment(pair<int,int> cell) {
        auto it = find(this->commitments->begin(), this->commitments->end(), cell);
        if (it != this->commitments->end()) {
            this->commitments->erase(it);
        }
    }

    void addDependency(pair<int,int> cell) {
        this->dependencies->push_back(cell);
    }

    void removeAllDependencies() {
        this->dependencies->clear();
    }
};

struct Token {
    char letter;
    int number;
};

struct Entry {
    Token first;
    std::optional<Token> second;
};

class Excel {
private:
    vector<vector<Cell>> Sheet;

    void recalculate(pair<int,int>& cell, bool updateValues) {
        cout<<cell.first<<","<<cell.second<<endl;
        int newValue = 0;

        for(auto dep: *Sheet[cell.first][cell.second].dependencies) {
            newValue += Sheet[dep.first][dep.second].Value;
        }

        if (newValue != Sheet[cell.first][cell.second].Value || updateValues) {
            Sheet[cell.first][cell.second].Value = newValue;

            for(auto dep: *Sheet[cell.first][cell.second].commitments) {
                recalculate(dep, false);
            }
        }
    }

    std::optional<Entry> parse_one(const std::string& s) {
        static const std::regex re(R"(^([A-Z])([0-9]+)(?::([A-Z])([0-9]+))?$)");
        std::smatch m;
        if (!std::regex_match(s, m, re)) return std::nullopt;

        Entry e{
            Token{ m[1].str()[0], std::stoi(m[2].str()) },
            std::nullopt
        };
        if (m[3].matched) {
            e.second = Token{ m[3].str()[0], std::stoi(m[4].str()) };
        }
        return e;
    }

    vector<pair<int,int>>* getDependentCells(vector<string>& numbers) {
        auto dependencies = new vector<pair<int,int>>();

        for (const auto& s : numbers) {
            auto parsed = parse_one(s);
            const Entry& e = *parsed;
            if (e.second) {
                for (int i = e.first.number-1; i < e.second->number; i++) {
                    for (int j = e.first.letter-'A'; j <= e.second->letter-'A'; j++) {
                        dependencies->push_back(make_pair(i, j));
                    }
                }
            } else {
                dependencies->push_back(make_pair(e.first.number-1, e.first.letter-'A'));
            }
        }

        return dependencies;
    }

public:
    Excel(int height, char width) {
        Sheet = vector<vector<Cell>>();
        for (int i = 0; i < height; i++) {
            vector<Cell> row;
            for (int j = 0; j < width-'A'+1; j++) {
                row.push_back(Cell(new vector<pair<int,int>>({make_pair(i, j)})));
            }
            Sheet.push_back(row);
        }
    }
    
    void set(int row, char column, int val) {
        cout<<"set:"<<row<<","<<column<<endl;
        Cell* currentCell = &Sheet[row-1][column-'A'];
        
        for(auto cell: *currentCell->dependencies) {
            auto tmp = make_pair(row-1, column-'A');
            Sheet[cell.first][cell.second].removeCommitment(tmp);
        }

        currentCell->removeAllDependencies();

        bool updateValues = (currentCell->Value != val);
        currentCell->Value = val;
        
        auto cell = make_pair(row-1, column-'A');
        currentCell->addDependency(cell);
        
        recalculate(cell, updateValues);
    }
    
    int get(int row, char column) {
        cout<<"get:"<<row<<","<<column<<endl;
        return Sheet[row-1][column-'A'].Value;
    }
    
    int sum(int row, char column, vector<string> numbers) {
        cout<<"sum:"<<row<<","<<column<<endl;
        Sheet[row-1][column-'A'].dependencies = getDependentCells(numbers);
        
        for(auto cell: *Sheet[row-1][column-'A'].dependencies) {
            Sheet[cell.first][cell.second].addCommitment(make_pair(row-1,column-'A'));
        }

        auto tmp = make_pair(row-1, column-'A');
        recalculate(tmp, false);
        
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