https://leetcode.com/discuss/interview-question/5829286/Google-Winter-Interview-Experience(On-Campus)

// Adjacency list for the tree
vector<vector<int>> tree;
vector<char> colors; // 'R' or 'B'
int numNodes;        // Total number of nodes

/**
 * Checks if the tree can be rooted at `root` while satisfying:
 * 1. Each node has at most 2 children.
 * 2. Adjacent nodes have different colors.
 * 3. All nodes at the same level have the same color.
 * 
 * @param root The node to check as the root.
 * @return True if the root satisfies the conditions, otherwise False.
 */
bool isValidRoot(int root) {
    queue<int> q;                   // BFS queue
    vector<int> levels(numNodes, -1); // To store the level of each node
    unordered_map<int, char> levelColors; // Expected color for each level

    q.push(root);
    levels[root] = 0;
    levelColors[0] = colors[root]; // Root's color determines level 0 color

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        int currentLevel = levels[currentNode];
        char currentColor = colors[currentNode];

        // Ensure adjacent nodes have different colors
        for (int neighbor : tree[currentNode]) {
            if (levels[neighbor] == -1) {
                // If the neighbor is unvisited, assign its level and enqueue
                levels[neighbor] = currentLevel + 1;
                q.push(neighbor);

                // Set the expected color for this level if not already set
                if (levelColors.find(levels[neighbor]) == levelColors.end()) {
                    levelColors[levels[neighbor]] = (currentColor == 'R') ? 'B' : 'R';
                }

                // Ensure the neighbor's color matches the expected level color
                if (colors[neighbor] != levelColors[levels[neighbor]]) {
                    return false;
                }
            } else {
                // Neighbor is already visited; ensure its color is different
                if (colors[neighbor] == currentColor) {
                    return false;
                }
            }
        }
    }

    return true;
}

/**
 * Finds a valid root for the tree that satisfies the conditions.
 * 
 * @return The root node index if found, otherwise -1.
 */
int findValidRoot() {
    for (int i = 0; i < numNodes; i++) {
        // Only consider nodes with at most 2 neighbors as potential roots
        if (tree[i].size() <= 2) {
            if (isValidRoot(i)) {
                return i;
            }
        }
    }

    return -1; // No valid root found
}

int main() {
    cin >> numNodes;
    tree.resize(numNodes);
    colors.resize(numNodes);

    // Input edges for the tree
    for (int i = 0; i < numNodes - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--; // Convert to 0-based indexing
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // Input colors for each node
    for (int i = 0; i < numNodes; i++) {
        cin >> colors[i];
    }

    // Find and print the valid root
    int validRoot = findValidRoot();
    cout << validRoot + 1 << endl; // Convert back to 1-based indexing for output

    return 0;
}
