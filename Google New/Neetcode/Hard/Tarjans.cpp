https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/description/
class Solution {
public:
    int ROWS, COLS;

    void dfs(int r, int c, vector<vector<int>>& grid, set<pair<int, int>>& visit) {
        if (r < 0 || c < 0 || r >= ROWS || c >= COLS || grid[r][c] == 0 || visit.count({r, c})) {
            return;
        }

        visit.insert({r, c});
        vector<pair<int, int>> neighbors = {{r + 1, c}, {r - 1, c}, {r, c + 1}, {r, c - 1}};

        for (auto [nr, nc] : neighbors) {
            dfs(nr, nc, grid, visit);
        }
    }

    int count_islands(vector<vector<int>>& grid) {
        set<pair<int, int>> visit;
        int count = 0;

        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                if (grid[r][c] == 1 && !visit.count({r, c})) {
                    dfs(r, c, grid, visit);
                    count++;
                }
            }
        }

        return count;
    }

    int minDays(vector<vector<int>>& grid) {
        ROWS = grid.size();
        COLS = grid[0].size();

        // Check initial island count
        if (count_islands(grid) != 1) {
            return 0;
        }

        // Try removing each land cell
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                if (grid[r][c] == 0) {
                    continue;
                }

                grid[r][c] = 0; // Temporarily remove the land cell
                if (count_islands(grid) != 1) {
                    return 1;
                }
                grid[r][c] = 1; // Restore the land cell
            }
        }

        return 2; // If no single removal disconnects the island
    }
};
