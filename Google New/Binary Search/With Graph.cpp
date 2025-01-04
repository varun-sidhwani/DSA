
https://leetcode.com/discuss/interview-question/5963260/Google-India-Interview-Experience-or-L4-or-phone-screen-or-onsite-or-reject
last round.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

struct Edge {
    int u, v, weight;
};

class Graph {
private:
    int V; // Number of vertices
    vector<Edge> edges; // List of edges
    vector<int> colors; // Colors of the vertices
    vector<vector<int>> adj; // Adjacency list for the filtered graph

    // Build the subgraph with edges >= W
    void buildSubgraph(int W) {
        adj.assign(V, vector<int>());
        for (const auto& edge : edges) {
            if (edge.weight >= W) {
                adj[edge.u].push_back(edge.v);
                adj[edge.v].push_back(edge.u);
            }
        }
    }

    // Perform BFS to check if all nodes of a specific color are connected
    bool isConnected(int color) {
        vector<bool> visited(V, false);
        queue<int> q;

        // Start BFS from the first unvisited node of this color
        for (int i = 0; i < V; ++i) {
            if (colors[i] == color) {
                q.push(i);
                visited[i] = true;
                break;
            }
        }

        // Perform BFS for the color group
        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node]) {
                if (!visited[neighbor] && colors[neighbor] == color) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // Verify all nodes of the same color are visited
        for (int i = 0; i < V; ++i) {
            if (colors[i] == color && !visited[i]) {
                return false; // Not connected
            }
        }
        return true; // All nodes of the color are connected
    }

public:
    Graph(int vertices, const vector<Edge>& edgeList, const vector<int>& colorList)
        : V(vertices), edges(edgeList), colors(colorList) {}

    int findMaxWeight() {
        int low = 0, high = 0;

        // Determine the range of weights
        for (const auto& edge : edges) {
            high = max(high, edge.weight);
        }

        int result = 0;

        // Binary search for the maximum weight
        while (low <= high) {
            int mid = (low + high) / 2;

            // Build subgraph for edges >= mid
            buildSubgraph(mid);

            // Check if all color groups are connected
            bool valid = true;
            unordered_map<int, bool> checkedColors; // Track already checked colors
            for (int i = 0; i < V; ++i) {
                int color = colors[i];
                if (!checkedColors[color]) {
                    checkedColors[color] = true;
                    if (!isConnected(color)) {
                        valid = false;
                        break;
                    }
                }
            }

            if (valid) {
                result = mid; // Update result and try a higher weight
                low = mid + 1;
            } else {
                high = mid - 1; // Try a lower weight
            }
        }

        return result;
    }
};
