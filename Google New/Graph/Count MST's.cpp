#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Check if two intervals overlap
bool intervalsOverlap(int start1, int end1, int start2, int end2) {
    return max(start1, start2) <= min(end1, end2);
}

// Build the graph adjacency list
vector<vector<int>> buildGraph(int n, const vector<pair<int, int>>& intervals) {
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (intervalsOverlap(intervals[i].first, intervals[i].second,
                                 intervals[j].first, intervals[j].second)) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    return adj;
}

// Check if the graph is connected using BFS
bool isConnected(const vector<vector<int>>& adj, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;

    int count = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return count == n;
}

// Recursive DFS to count spanning trees
int countSpanningTrees(int node, vector<vector<int>>& adj, vector<bool>& visited,
                       int edgesUsed, int n) {
    if (edgesUsed == n - 1) {
        return 1; // A spanning tree is found
    }

    visited[node] = true;
    int count = 0;

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            count += countSpanningTrees(neighbor, adj, visited, edgesUsed + 1, n);
        }
    }

    visited[node] = false;
    return count;
}

int main() {
    int n; // Number of vertices
    cin >> n;

    vector<pair<int, int>> intervals(n);
    for (int i = 0; i < n; ++i) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    // Build the graph adjacency list
    vector<vector<int>> adj = buildGraph(n, intervals);

    // Check if the graph is connected
    if (!isConnected(adj, n)) {
        cout << 0 << endl; // No spanning trees if the graph is not connected
        return 0;
    }

    // Count all spanning trees using DFS
    vector<bool> visited(n, false);

    // Start DFS from the first node
    int result = countSpanningTrees(0, adj, visited, 0, n);

    cout << result << endl;
    return 0;
}
