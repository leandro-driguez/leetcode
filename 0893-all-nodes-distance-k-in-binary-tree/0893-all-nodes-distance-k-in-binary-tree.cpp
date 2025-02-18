/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    bool rootToTarget(TreeNode* node, TreeNode* target, vector<TreeNode*>& path) {
        if (!node)
            return false;

        if (node == target) {
            path.push_back(node);
            return true;
        }

        path.push_back(node);
        if (rootToTarget(node->left, target, path) || rootToTarget(node->right, target, path))
            return true;
        path.pop_back();

        return false;
    }

    void addNodesK(TreeNode* root, TreeNode* target, int k, vector<int>& nodesK) {
        if (k < 0 || !root)
            return;

        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            if (node.second == k)
                nodesK.push_back(node.first->val);
            else {
                if (node.first->left && node.first->left != target) {
                    q.push({node.first->left, node.second+1});
                }
                if (node.first->right && node.first->right != target) {
                    q.push({node.first->right, node.second+1});
                }
            }
        }
    }

public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        if (k == 0)
            return {target->val};
            
        vector<TreeNode*> path;
        rootToTarget(root, target, path);

        k--;

        vector<int> nodesK;
        if (target->left) {
            addNodesK(target->left, nullptr, k, nodesK);
        }
        if (target->right) {
            addNodesK(target->right, nullptr, k, nodesK);
        }

        for (int i = path.size()-1; i > 0; i--) {
            TreeNode* father = path[i-1];
            TreeNode* child  = path[i];

            addNodesK(father, child, k, nodesK);

            k--;
        }

        return nodesK;
    }
};