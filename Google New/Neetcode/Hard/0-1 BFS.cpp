https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/description/

class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // Deque for 0-1 BFS: (number of obstacles removed, row, col)
        deque<tuple<int, int, int>> dq;
        dq.push_front({0, 0, 0}); // Start from the top-left corner

        // Set to track visited cells
        set<pair<int, int>> visited;
        visited.insert({0, 0});

        // Direction vectors for moving up, down, left, right
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!dq.empty()) {
            auto [obstacles, r, c] = dq.front();
            dq.pop_front();

            // If we reach the bottom-right corner, return the number of obstacles removed
            if (r == rows - 1 && c == cols - 1) {
                return obstacles;
            }

            // Explore neighbors
            for (auto [dr, dc] : directions) {
                int nr = r + dr;
                int nc = c + dc;

                // Check boundary conditions and if the cell is already visited
                if (nr < 0 || nc < 0 || nr >= rows || nc >= cols || visited.count({nr, nc})) {
                    continue;
                }

                // Mark as visited
                visited.insert({nr, nc});

                // If there's an obstacle, push it to the back of the deque
                if (grid[nr][nc] == 1) {
                    dq.push_back({obstacles + 1, nr, nc});
                } else { // If no obstacle, push it to the front of the deque
                    dq.push_front({obstacles, nr, nc});
                }
            }
        }

        return -1; // If we cannot reach the bottom-right corner
    }
};