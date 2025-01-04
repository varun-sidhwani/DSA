https://leetcode.com/problems/sliding-puzzle/

class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        // Define the adjacency list for the graph representation of valid swaps
        vector<vector<int>> adj = {
            {1, 3},       // 0
            {0, 2, 4},    // 1
            {1, 5},       // 2
            {0, 4},       // 3
            {1, 3, 5},    // 4
            {2, 4}        // 5
        };

        // Convert the board into a string for easier manipulation
        string start;
        for (auto& row : board) {
            for (int c : row) {
                start += to_string(c);
            }
        }

        // Target configuration
        string target = "123450";

        // BFS queue: (index of zero, board state, length of path)
        queue<pair<int, pair<string, int>>> q;
        q.push({start.find('0'), {start, 0}});

        // Visited set to avoid revisiting states
        unordered_set<string> visited;
        visited.insert(start);

        // BFS loop
        while (!q.empty()) {
            auto [i, statePair] = q.front();
            q.pop();
            string currentState = statePair.first;
            int steps = statePair.second;

            // If we reach the target configuration
            if (currentState == target) {
                return steps;
            }

            // Convert the current board state into a mutable string array
            for (int j : adj[i]) {
                string nextState = currentState;
                swap(nextState[i], nextState[j]); // Swap '0' with the neighbor position

                // If the new state hasn't been visited, add it to the queue
                if (visited.find(nextState) == visited.end()) {
                    visited.insert(nextState);
                    q.push({j, {nextState, steps + 1}});
                }
            }
        }

        // If no solution is found, return -1
        return -1;
    }
};