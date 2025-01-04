https://leetcode.com/discuss/interview-question/5039879/Google-Onsite-Interview

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <sstream>

using namespace std;

// Trie Node Structure
struct TrieNode {
    unordered_map<string, TrieNode*> children; // Map for children nodes
    bool isFile = false; // Flag to indicate if the node is a file
    bool isSelected = false; // Flag to indicate if the node is selected
};

// Insert a path into the trie
void insertPath(TrieNode* root, const string& path) {
    TrieNode* current = root;
    stringstream ss(path);
    string part;
    while (getline(ss, part, '/')) {
        if (part.empty()) continue; // Skip empty parts
        if (!current->children.count(part)) {
            current->children[part] = new TrieNode();
        }
        current = current->children[part];
    }
    current->isFile = path.find('.') != string::npos; // Mark as file if it contains a '.'
}

// Mark selected paths in the trie
void markSelected(TrieNode* root, const string& path) {
    TrieNode* current = root;
    stringstream ss(path);
    string part;
    while (getline(ss, part, '/')) {
        if (part.empty()) continue;
        if (!current->children.count(part)) return; // If path doesn't exist, ignore
        current = current->children[part];
    }
    current->isSelected = true; // Mark as selected
}

// Post-order traversal to determine the output
void collectOutput(TrieNode* node, const string& currentPath, vector<string>& output) {
    if (node->children.empty()) {
        // Leaf node
        if (node->isSelected) {
            output.push_back(currentPath);
        }
        return;
    }

    bool allSelected = true;
    vector<string> tempOutput;

    for (auto& [name, child] : node->children) {
        string newPath = currentPath + "/" + name;
        collectOutput(child, newPath, tempOutput);
        if (!child->isSelected && !child->children.empty()) {
            allSelected = false;
        }
    }

    if (allSelected && !tempOutput.empty()) {
        output.push_back(currentPath);
    } else {
        output.insert(output.end(), tempOutput.begin(), tempOutput.end());
    }
}

int main() {
    // Input data
    vector<string> directories = {
        "/a/b/x.txt",
        "/a/b/p.txt",
        "/a/c",
        "/a/d/y.txt",
        "/a/d/z.txt"
    };
    vector<string> selected = {
        "/a/d/y.txt",
        "/a/d/z.txt",
        "/a/b/p.txt"
    };

    // Step 1: Build the trie
    TrieNode* root = new TrieNode();
    for (const auto& path : directories) {
        insertPath(root, path);
    }

    // Step 2: Mark selected paths
    for (const auto& path : selected) {
        markSelected(root, path);
    }

    // Step 3: Collect output
    vector<string> output;
    collectOutput(root, "", output);

    // Step 4: Print output
    sort(output.begin(), output.end());
    for (const auto& path : output) {
        cout << path << endl;
    }

    return 0;
}
