class DSU {
public:
    unordered_map<string,string> root;
    unordered_map<string,int> rank;

    DSU() { }

    string Find(string x) {
        if (root.find(x) == root.end()) {
            root[x] = x;
            rank[x] = 1;
        }
        if (root[x] == x)
            return x;
        return root[x] = Find(root[x]);
    }

    void Union(string x, string y) {
        string rootX = Find(x);
        string rootY = Find(y);

        if (rootX != rootY) {
            if (rank[rootX] == rank[rootY])
                rank[rootX]++;
            if (rank[rootX] > rank[rootY])
                root[rootY] = rootX;
            else 
                root[rootX] = rootY;
        }
    }
};


string removeIndex(string s) {
    int i = s.size()-1;
    for (; i >= 0; i--){
        if (s[i] == '_')
            break;
    }
    string ans = "";
    for (int j = 0; j < i; j++) {
        ans += s[j];
    }
    return ans;
}

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        auto dsu = DSU();
        for (int i = 0; i < accounts.size(); i++) {
            accounts[i][0] += "_" + to_string(i) + ".";
            for (int j = 1; j < accounts[i].size(); j++) {
                dsu.Union(accounts[i][j-1], accounts[i][j]);
            }
        }

        unordered_map<string,vector<string>> mergedAccounts;
        for (auto it = dsu.root.begin(); it != dsu.root.end(); ++it) {
            if (it->first[it->first.size()-1] == '.')
                continue;

            dsu.Find(it->first);
            mergedAccounts[dsu.root[it->first]].push_back(it->first);
        }

        vector<vector<string>> ans;
        for (auto it = mergedAccounts.begin(); it != mergedAccounts.end(); ++it) {
            sort(it->second.begin(), it->second.end());
            it->second.insert(it->second.begin(), removeIndex(it->first));
            ans.push_back(it->second);
        }

        return ans;
    }
};