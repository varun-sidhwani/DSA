https://leetcode.com/discuss/interview-question/6033838/Google-or-Virtual-Interview-or-Count-Nodes


Using UNION FIND

vector<int> countConnectedComponents(int n, vector<vector<int>>& edges, vector<vector<int>>& edgesToRemove) {
    UnionFind uf(n);

    // Mark edges to remove
    unordered_set<string> edgesSet;
    for (const auto& edge : edgesToRemove) {
        edgesSet.insert(to_string(edge[0]) + "," + to_string(edge[1]));
        edgesSet.insert(to_string(edge[1]) + "," + to_string(edge[0]));
    }

    // Union all edges except those in edgesToRemove
    for (const auto& edge : edges) {
        if (edgesSet.find(to_string(edge[0]) + "," + to_string(edge[1])) == edgesSet.end()) {
            uf.unite(edge[0], edge[1]);
        }
    }

    // Find the sizes of all connected components
    unordered_map<int, int> componentSize;
    for (int i = 1; i <= n; ++i) {
        int root = uf.find(i);
        componentSize[root] = uf.getSize(root);
    }

    // Collect the sizes into a result vector
    vector<int> result;
    for (const auto& [root, size] : componentSize) {
        result.push_back(size);
    }

    return result;
}


USING DFS


#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Helper function to perform DFS and calculate the component size
int dfs(int node, unordered_map<int, vector<int>>& graph, unordered_set<int>& visited) {
    visited.insert(node);
    int size = 1; // Count the current node

    for (int neighbor : graph[node]) {
        if (visited.find(neighbor) == visited.end()) {
            size += dfs(neighbor, graph, visited);
        }
    }

    return size;
}

vector<int> countConnectedComponents(int n, vector<vector<int>>& edges, vector<vector<int>>& edgesToRemove) {
    // Create the adjacency list
    unordered_map<int, vector<int>> graph;
    for (int i = 1; i <= n; ++i) {
        graph[i] = {};
    }

    // Add edges to the adjacency list (directed)
    unordered_set<string> edgesSet;
    for (const auto& edge : edgesToRemove) {
        edgesSet.insert(to_string(edge[0]) + "," + to_string(edge[1]));
    }

    for (const auto& edge : edges) {
        if (edgesSet.find(to_string(edge[0]) + "," + to_string(edge[1])) == edgesSet.end()) {
            graph[edge[0]].push_back(edge[1]);
        }
    }

    // Find connected components using DFS
    unordered_set<int> visited;
    vector<int> componentSizes;

    for (int i = 1; i <= n; ++i) {
        if (visited.find(i) == visited.end()) {
            int size = dfs(i, graph, visited);
            componentSizes.push_back(size);
        }
    }

    return componentSizes;
} 
