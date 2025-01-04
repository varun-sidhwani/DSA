// Given a binary search tree, and a range [L, R], find all keys that lie within the range.

// Recursive Approach

#include <iostream>
#include <vector>
using namespace std;

// Definition of a tree node
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : key(x), left(nullptr), right(nullptr) {}
};

// Function to find keys in the range [L, R]
void findKeysInRange(TreeNode* root, int L, int R, vector<int>& result) {
    if (!root) return;

    // If the current node's key is greater than L, explore the left subtree
    if (root->key > L) {
        findKeysInRange(root->left, L, R, result);
    }

    // If the current node's key is within the range, add it to the result
    if (L <= root->key && root->key <= R) {
        result.push_back(root->key);
    }

    // If the current node's key is less than R, explore the right subtree
    if (root->key < R) {
        findKeysInRange(root->right, L, R, result);
    }
}


// Helper function to create a BST node
TreeNode* insert(TreeNode* root, int key) {
    if (!root) return new TreeNode(key);
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    return root;
}

int main() {
    // Constructing a BST
    TreeNode* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 13);
    root = insert(root, 18);

    // Range [L, R]
    int L = 6, R = 14;

    // Find and print keys in the range
    vector<int> result;
    findKeysInRange(root, L, R, result);

    cout << "Keys in range [" << L << ", " << R << "]: ";
    for (int key : result) {
        cout << key << " ";
    }
    cout << endl;

    return 0;
}


// Iterative Approach

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Definition of a tree node
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : key(x), left(nullptr), right(nullptr) {}
};

// Function to find keys in the range [L, R] using an iterative approach
vector<int> findKeysInRangeIterative(TreeNode* root, int L, int R) {
    vector<int> result;
    if (!root) return result;

    stack<TreeNode*> s;
    TreeNode* current = root;

    while (!s.empty() || current != nullptr) {
        // Go to the leftmost node
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }

        // Process the node at the top of the stack
        current = s.top();
        s.pop();

        // If the node's key is within the range, add it to the result
        if (L <= current->key && current->key <= R) {
            result.push_back(current->key);
        }

        // If the node's key is greater than R, we can stop processing
        if (current->key > R) {
            break;
        }

        // Move to the right subtree
        current = current->right;
    }

    return result;
}

// Helper function to create a BST node
TreeNode* insert(TreeNode* root, int key) {
    if (!root) return new TreeNode(key);
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    return root;
}

int main() {
    // Constructing a BST
    TreeNode* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 13);
    root = insert(root, 18);

    // Range [L, R]
    int L = 6, R = 14;

    // Find and print keys in the range
    vector<int> result = findKeysInRangeIterative(root, L, R);

    cout << "Keys in range [" << L << ", " << R << "]: ";
    for (int key : result) {
        cout << key << " ";
    }
    cout << endl;

    return 0;
}
