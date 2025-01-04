

#include <string>
#include <unordered_set>

// Helper function to serialize a subtree into a canonical form
string getCanonicalForm(TreeNode* node) {
    if (!node) return "#";  // null child
    
    // Recursively get forms for left & right subtrees
    string leftForm = getCanonicalForm(node->left);
    string rightForm = getCanonicalForm(node->right);
    
    // Combine into a structured string
    // For a binary tree, left and right order is significant
    return "(" + leftForm + ")" + "(" + rightForm + ")";
}

// Helper DFS to mark visited nodes so we don't re-count the same island
// This could be optional if you only do the canonical form once per island.
void dfsMark(TreeNode* node) {
    if (!node || node->val == 0) return;
    node->val = 0;
    dfsMark(node->left);
    dfsMark(node->right);
}

// Helper function: for each '1'-valued node (island root), get canonical form
void traverseForNonIsoIslands(TreeNode* node, unordered_set<string>& uniqueStructures) {
    if (!node) return;

    // If we encounter a '1', it indicates a new island
    if (node->val == 1) {
        // Get the canonical form of this island's subtree
        string cForm = getCanonicalForm(node);
        uniqueStructures.insert(cForm);
        
        // Optionally mark the entire island visited
        // to avoid re-checking the same nodes.
        dfsMark(node);
    }
    
    traverseForNonIsoIslands(node->left, uniqueStructures);
    traverseForNonIsoIslands(node->right, uniqueStructures);
}

// Main function to count distinct isomorphic island structures
int countDistinctIsomorphicIslands(TreeNode* root) {
    if (!root) return 0;
    
    unordered_set<string> uniqueStructures;
    traverseForNonIsoIslands(root, uniqueStructures);
    return static_cast<int>(uniqueStructures.size());
}
