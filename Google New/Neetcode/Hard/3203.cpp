https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/

class Solution {
public:
    // Function to build adjacency list from edges
    vector<vector<int>> buildAdjList(vector<vector<int>>& edges, int n) {
        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        return adj;
    }

    // DFS to compute diameter and maximum leaf path
    pair<int, int> getDiameter(int cur, int parent, vector<vector<int>>& adj) {
        int maxDiameter = 0;
        priority_queue<int, vector<int>, greater<int>> maxChildPaths; // Min-heap for top 2 largest paths

        for (int neighbor : adj[cur]) {
            if (neighbor == parent) continue;

            auto [neiDiameter, neiMaxLeafPath] = getDiameter(neighbor, cur, adj);

            // Update max diameter
            maxDiameter = max(maxDiameter, neiDiameter);

            // Track the top two maximum child leaf paths
            maxChildPaths.push(neiMaxLeafPath);
            if (maxChildPaths.size() > 2) {
                maxChildPaths.pop();
            }
        }

        // Sum of the two largest child paths
        int maxSumChildPaths = 0;
        while (!maxChildPaths.empty()) {
            maxSumChildPaths += maxChildPaths.top();
            maxChildPaths.pop();
        }

        // Update the diameter using the two largest paths
        maxDiameter = max(maxDiameter, maxSumChildPaths);

        return {maxDiameter, 1 + maxSumChildPaths};
    }

    // Main function to compute the minimum diameter after merging two trees
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n1 = edges1.size() + 1; // Number of nodes in tree 1
        int n2 = edges2.size() + 1; // Number of nodes in tree 2

        // Build adjacency lists
        vector<vector<int>> adj1 = buildAdjList(edges1, n1);
        vector<vector<int>> adj2 = buildAdjList(edges2, n2);

        // Compute diameters and max leaf paths for both trees
        auto [d1, maxLeafPath1] = getDiameter(0, -1, adj1);
        auto [d2, maxLeafPath2] = getDiameter(0, -1, adj2);

        // Merge the two trees and calculate the new diameter
        return max(d1, max(d2, (int)ceil(d1 / 2.0) + (int)ceil(d2 / 2.0) + 1));
    }
};
