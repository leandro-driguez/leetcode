/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    vector<TreeNode*> generateTrees(int n, int id) {
        if (n == 0)
            return {nullptr};
        
        vector<TreeNode*> trees;
        for (int i = 0; i < n; i++) {
            for(auto leftTree: generateTrees(i, id-n+i)) {
                for (auto rightTree: generateTrees(n-1-i, id)) {
                    auto node = new TreeNode(id-n+i+1);
                    node->left = leftTree;
                    node->right = rightTree;
                    trees.push_back(node);
                }
            }
        }
        return trees;
    }
public:
    vector<TreeNode*> generateTrees(int n) {
        return generateTrees(n, n);
    }
};