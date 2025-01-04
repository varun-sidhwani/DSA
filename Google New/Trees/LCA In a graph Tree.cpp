#include <iostream>
#include <vector>
using namespace std;

class GraphTreeLCA {
public:
    vector<vector<int>> adj;  // Adjacency list
    vector<int> parent;       // Parent of each node
    vector<int> depth;        // Depth of each node

    GraphTreeLCA(int n) : adj(n), parent(n, -1), depth(n, 0) {}

    // Add edge between two nodes
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);  // Since it's an undirected tree
    }

    // Precompute parent and depth using DFS
    void dfs(int node, int par) {
        parent[node] = par;
        for (int neighbor : adj[node]) {
            if (neighbor != par) {  // Avoid backtracking to the parent
                depth[neighbor] = depth[node] + 1;
                dfs(neighbor, node);
            }
        }
    }

    // Find LCA of nodes u and v
    int findLCA(int u, int v) {
        // Step 1: Bring both nodes to the same depth
        while (depth[u] > depth[v]) {
            u = parent[u];
        }
        while (depth[v] > depth[u]) {
            v = parent[v];
        }

        // Step 2: Move both nodes up until they meet
        while (u != v) {
            u = parent[u];
            v = parent[v];
        }

        return u;  // This is the LCA
    }
};

int main() {
    int n = 7;  // Number of nodes
    GraphTreeLCA tree(n);

    // Add edges
    tree.addEdge(0, 1);
    tree.addEdge(0, 2);
    tree.addEdge(1, 3);
    tree.addEdge(1, 4);
    tree.addEdge(2, 5);
    tree.addEdge(2, 6);

    // Precompute parent and depth starting from node 0
    tree.dfs(0, -1);

    // Find LCA of nodes
    cout << "LCA of 3 and 4: " << tree.findLCA(3, 4) << endl;  // Output: 1
    cout << "LCA of 3 and 6: " << tree.findLCA(3, 6) << endl;  // Output: 0
    cout << "LCA of 5 and 6: " << tree.findLCA(5, 6) << endl;  // Output: 2

    return 0;
}
