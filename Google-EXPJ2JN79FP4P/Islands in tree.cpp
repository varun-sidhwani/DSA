Count Islands in tree
https://leetcode.com/discuss/interview-question/5782507/Google-L4-or-Accepted-or-HyderabadPune
#include <iostream>
using namespace std;

// Binary Tree Node Definition
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// DFS Function to mark visited nodes
void dfs(TreeNode* node) {
    if (!node || node->val == 0) return;
    
    // Mark the node as visited by setting val = 0
    node->val = 0;
    
    // Traverse left and right children
    dfs(node->left);
    dfs(node->right);
}

// Count Islands Function
int countIslands(TreeNode* root) {
    if (!root) return 0;

    int totalIslands = 0;
    
    // If current node is an unvisited '1', we've found a new island
    if (root->val == 1) {
        totalIslands++;
        dfs(root);  // Mark all connected '1's in this island
    }
    
    // Recursively count in subtrees
    totalIslands += countIslands(root->left);
    totalIslands += countIslands(root->right);
    
    return totalIslands;
}



// Find Uniqe Size Islands

// Helper DFS to return size of the connected component
int dfsIslandSize(TreeNode* node) {
    if (!node || node->val == 0) return 0;

    // Mark as visited
    node->val = 0;
    
    // Count current node + size of children
    return 1 + dfsIslandSize(node->left) + dfsIslandSize(node->right);
}

// Helper function to traverse the tree and collect island sizes
void traverseAndCollectSizes(TreeNode* node, set<int>& uniqueSizes) {
    if (!node) return;
    
    if (node->val == 1) {
        int size = dfsIslandSize(node);  // get the size of this island
        uniqueSizes.insert(size);
    }
    
    traverseAndCollectSizes(node->left, uniqueSizes);
    traverseAndCollectSizes(node->right, uniqueSizes);
}

// Main function to return the number of distinct island sizes
int countDistinctIslandSizes(TreeNode* root) {
    if (!root) return 0;
    
    set<int> uniqueSizes;
    traverseAndCollectSizes(root, uniqueSizes);
    return static_cast<int>(uniqueSizes.size());
}




int sizeOfIsland(root){
    if(!root || root->val == 0)
        return 0;

    root->val = 0;

    return 1 + dfs(root->left) + dfs(root->right);
}


void findMaxSize(root){

    if(!root)
        return;

    int maxSize = 0;

    if(root->val == 1){
        int size = sizeOfIsland(root);
        maxSize = max(maxSize, size);
    }

    return max(maxSize, max(findMaxSize(root->left), findMaxSize(root->right)));


}


// Find Max Size of Island 

int sizeOfIsland(TreeNode* root) {
    if (!root || root->val == 0) {
        return 0;
    }

    // Mark the current node as visited
    root->val = 0;

    // Recursively calculate the size of the island
    return 1 + sizeOfIsland(root->left) + sizeOfIsland(root->right);
}

int findMaxSize(TreeNode* root) {
    if (!root) {
        return 0;
    }

    int maxSize = 0;

    if (root->val == 1) {
        // Calculate the size of the current island
        int size = sizeOfIsland(root);
        maxSize = max(maxSize, size);
    }

    // Recursively find the maximum size in left and right subtrees
    return max(maxSize, max(findMaxSize(root->left), findMaxSize(root->right)));
}
