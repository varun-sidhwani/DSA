#include <bits/stdc++.h>
using namespace std;

struct Node {
    string name;
    string value;
    vector<Node*> children;

    Node() : name(""), value("") {}
    Node(const string& n, const string& v) : name(n), value(v) {}
};


Node* clone(const Node* root) {
    if (!root) return nullptr;
    Node* newRoot = new Node(root->name, root->value);
    for (auto* child : root->children) {
        newRoot->children.push_back(clone(child));
    }
    return newRoot;
}

Node* merge(Node* t1, Node* t2);


vector<Node*> mergeChildren(const vector<Node*>& c1, const vector<Node*>& c2) {
    vector<Node*> result;
    // Track which children of c2 have been merged already
    vector<bool> used(c2.size(), false);

    // 1) For each child in c1, try to find a match in c2
    for (auto* child1 : c1) {
        bool foundMatch = false;
        for (int j = 0; j < (int)c2.size(); j++) {
            if (!used[j] && child1->name == c2[j]->name) {
                // Merge these two matching nodes
                used[j] = true;
                Node* mergedChild = merge(child1, c2[j]);
                result.push_back(mergedChild);
                foundMatch = true;
                break;
            }
        }
        // If no match found, clone from c1 as-is
        if (!foundMatch) {
            result.push_back(clone(child1));
        }
    }

    // 2) Append leftover children from c2 (those that were not merged)
    for (int j = 0; j < (int)c2.size(); j++) {
        if (!used[j]) {
            result.push_back(clone(c2[j]));
        }
    }

    return result;
}

Node* merge(Node* t1, Node* t2) {
    // Case 1: both null
    if (!t1 && !t2) return nullptr;
    // Case 2: one null
    if (!t1) return clone(t2);
    if (!t2) return clone(t1);

    // Case 3: both non-null
    if (t1->name == t2->name) {
        // They match by name => merge them
        Node* newNode = new Node(t1->name, t2->value); // override value with t2->value
        newNode->children = mergeChildren(t1->children, t2->children);
        return newNode;
    } else {
        Node* conflictParent = new Node("CONFLICT", "");
        conflictParent->children.push_back(clone(t1));
        conflictParent->children.push_back(clone(t2));
        return conflictParent;
    }
}


///

vector<Node*> mergeChildren(const vector<Node*>& c1, const vector<Node*>& c2) {
    vector<Node*> result;

    // Step 1: Create a hash map for children of c2
    unordered_map<string, Node*> mapC2;
    for (Node* child : c2) {
        mapC2[child->name] = child;
    }

    // Step 2: Process children of c1
    for (Node* child1 : c1) {
        if (mapC2.count(child1->name)) {
            // Match found: Merge the two nodes
            Node* mergedChild = merge(child1, mapC2[child1->name]);
            result.push_back(mergedChild);
            // Remove from the map to mark it as processed
            mapC2.erase(child1->name);
        } else {
            // No match: Add the child from c1 as-is
            result.push_back(clone(child1));
        }
    }

    // Step 3: Add remaining children from c2 (unmatched ones)
    for (auto& [name, child2] : mapC2) {
        result.push_back(clone(child2));
    }

    return result;
}
