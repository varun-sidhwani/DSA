class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // If the grid[0][1] or grid[1][0] is not reachable at time 1
        if (min(grid[0][1], grid[1][0]) > 1) {
            return -1;
        }

        // Min-heap priority queue to store {time, row, col}
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> minHeap;
        minHeap.push({0, 0, 0}); // Starting from {time=0, row=0, col=0}

        // Set to keep track of visited cells
        set<pair<int, int>> visited;

        // Direction vectors for neighbors (up, down, left, right)
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!minHeap.empty()) {
            auto [t, r, c] = minHeap.top();
            minHeap.pop();

            // If we reached the bottom-right cell
            if (r == rows - 1 && c == cols - 1) {
                return t;
            }

            // Mark the cell as visited
            if (visited.count({r, c})) {
                continue;
            }
            visited.insert({r, c});

            // Explore neighbors
            for (auto [dr, dc] : directions) {
                int nr = r + dr;
                int nc = c + dc;

                // Check boundary conditions and if the cell is already visited
                if (nr < 0 || nc < 0 || nr >= rows || nc >= cols || visited.count({nr, nc})) {
                    continue;
                }

                int wait = 0;

                // If time difference is even, we need to wait
                if (abs(grid[nr][nc] - t) % 2 == 0) {
                    wait = 1;
                }

                int newTime = max(grid[nr][nc] + wait, t + 1);

                // Push the new state into the heap
                minHeap.push({newTime, nr, nc});
            }
        }

        return -1; // If we exhaust the heap and cannot reach the target
    }
};
