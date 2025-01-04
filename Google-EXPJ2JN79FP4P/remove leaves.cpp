https://leetcode.com/discuss/interview-question/1693416/google-onsite-recursively-delete-leave-nodes-in-a-multi-tree

class Solution {
private:
    vector<vector<int>> result;

public:
    int getHeight(TreeNode* root) {
        if (!root) return -1;

        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        int currHeight = max(leftHeight, rightHeight) + 1;

        if (result.size() == currHeight) {
            result.emplace_back(); // Create space for the current height level
        }

        result[currHeight].push_back(root->val);
        return currHeight;
    }
    
    vector<vector<int>> findLeaves(TreeNode* root) {
        result.clear();
        getHeight(root);
        return result;
    }
};


// Using Topological Sort

class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> result;
        unordered_map<TreeNode*, TreeNode*> parentMap;
        queue<TreeNode*> leaves;

        // Helper function to perform DFS and build the parent map
        void buildParentMap(TreeNode* node, TreeNode* parent) {
            if (!node) return;
            parentMap[node] = parent;
            if (!node->left && !node->right) {
                leaves.push(node); // Node is a leaf
            }
            buildParentMap(node->left, node);
            buildParentMap(node->right, node);
        }

        // Step 1: Build the parent map and identify leaves
        buildParentMap(root, nullptr);

        // Step 2: Perform "onion peeling" layer by layer
        while (!leaves.empty()) {
            int n = leaves.size();
            vector<int> currentLayer;
            for (int i = 0; i < n; ++i) {
                TreeNode* leaf = leaves.front();
                leaves.pop();
                currentLayer.push_back(leaf->val);

                // Remove the leaf from its parent
                TreeNode* parent = parentMap[leaf];
                if (parent) {
                    if (parent->left == leaf) parent->left = nullptr;
                    if (parent->right == leaf) parent->right = nullptr;
                    // If parent becomes a leaf, add it to the queue
                    if (!parent->left && !parent->right) {
                        leaves.push(parent);
                    }
                }
            }
            result.push_back(currentLayer);
        }

        return result;
    }
};
