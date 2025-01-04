#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int res; // Result to count divisible components
    int k;   // Divisibility factor

    int dfs(int cur, int parent, vector<vector<int>>& adj, vector<int>& values) {
        int total = values[cur]; // Start with the current node's value

        for (int child : adj[cur]) {
            if (child != parent) { // Avoid traversing back to the parent
                total += dfs(child, cur, adj, values); // Add the total from the subtree
            }
        }

        // Check if the total is divisible by k
        if (total % k == 0) {
            res++;
            return 0; // Reset the total for this component
        }

        return total; // Return the total for further computation
    }

    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        // Initialize result and divisibility factor
        this->res = 0;
        this->k = k;

        // Create adjacency list
        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Start DFS from node 0 with no parent (-1)
        dfs(0, -1, adj, values);

        return res; // Return the final result
    }
};

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int res; // Result to count divisible components
    int k;   // Divisibility factor

    int dfs(int cur, int parent, vector<vector<int>>& adj, vector<int>& values) {
        int total = values[cur]; // Start with the current node's value

        for (int child : adj[cur]) {
            if (child != parent) { // Avoid traversing back to the parent
                total += dfs(child, cur, adj, values); // Add the total from the subtree
            }
        }

        // Check if the total is divisible by k
        if (total % k == 0) {
            res++;
            return 0; // Reset the total for this component
        }

        return total; // Return the total for further computation
    }

    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        // Initialize result and divisibility factor
        this->res = 0;
        this->k = k;

        // Create adjacency list
        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Start DFS from node 0 with no parent (-1)
        dfs(0, -1, adj, values);

        return res; // Return the final result
    }
};

