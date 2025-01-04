// A graph represented as an adjacency list where each node corresponds to a location, and edges represent paths between locations.
// A list of friends' starting locations (nodes).
// A list of cafes (nodes).
// Task: Find the cafe such that the maximum distance any friend has to travel to reach the cafe is minimized.

https://leetcode.com/discuss/interview-question/6034301/Google-Onsite-Reject

O(K * (E + V))


#include <bits/stdc++.h>
using namespace std;

// Function to find the best cafe based on minimizing the maximum distance
int findBestCafe(int n, const vector<vector<int>>& graph, const vector<int>& friends, const vector<int>& cafes) {
    int k = friends.size(); // Number of friends

    // dist[v][i] = distance from friend i to node v
    vector<vector<int>> dist(n, vector<int>(k, INT_MAX));

    // Multi-source BFS queue
    queue<pair<int, int>> q; // (node, friend_index)

    // Initialize distances for all friends' nodes and enqueue them
    for (int i = 0; i < k; ++i) {
        int start = friends[i];
        dist[start][i] = 0;
        q.push({start, i});
    }

    // Perform BFS
    while (!q.empty()) {
        auto [u, friend_idx] = q.front();
        q.pop();

        int current_dist = dist[u][friend_idx];
        for (int neighbor : graph[u]) {
            if (dist[neighbor][friend_idx] == INT_MAX) {
                dist[neighbor][friend_idx] = current_dist + 1;
                q.push({neighbor, friend_idx});
            }
        }
    }

    // Find the cafe that minimizes the maximum distance among friends
    int best_cafe = -1;
    int best_value = INT_MAX;

    for (int cafe_node : cafes) {
        // Compute the maximum distance from all friends to this cafe
        int mx = 0;
        for (int i = 0; i < k; ++i) {
            mx = max(mx, dist[cafe_node][i]);
        }
        // Pick the cafe if it has a smaller "max distance"
        if (mx < best_value) {
            best_value = mx;
            best_cafe = cafe_node;
        }
    }

    return best_cafe;
}

// Example usage
int main() {
    // Number of nodes and edges
    int n = 6, m = 7;

    // Graph adjacency list
    vector<vector<int>> graph(n);
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {2, 4}, {3, 5}, {4, 5}};
    for (auto [u, v] : edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Friends' initial positions
    vector<int> friends = {0, 3};

    // Cafes' locations
    vector<int> cafes = {4, 5};

    // Find the best cafe
    int best_cafe = findBestCafe(n, graph, friends, cafes);
    cout << "Best cafe is located at node: " << best_cafe << endl;

    return 0;
}
