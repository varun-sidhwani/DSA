https://leetcode.com/problems/sum-of-prefix-scores-of-strings/description/

class PrefixNode {
public:
    vector<PrefixNode*> children;
    int count;

    PrefixNode() : children(26, nullptr), count(0) {}
};

class PrefixTree {
private:
    PrefixNode* root;

public:
    PrefixTree() {
        root = new PrefixNode();
    }

    void insert(const string& word) {
        PrefixNode* cur = root;
        for (char c : word) {
            int i = c - 'a';
            if (!cur->children[i]) {
                cur->children[i] = new PrefixNode();
            }
            cur = cur->children[i];
            cur->count++;
        }
    }

    int get_score(const string& word) {
        PrefixNode* cur = root;
        int score = 0;
        for (char c : word) {
            int i = c - 'a';
            cur = cur->children[i];
            score += cur->count;
        }
        return score;
    }
};

class Solution {
public:
    vector<int> sumPrefixScores(vector<string>& words) {
        vector<int> res;
        PrefixTree prefix_tree;

        for (const string& word : words) {
            prefix_tree.insert(word);
        }

        for (const string& word : words) {
            res.push_back(prefix_tree.get_score(word));
        }

        return res;
    }
};
