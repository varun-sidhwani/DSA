https://leetcode.com/problems/construct-quad-tree/


class Solution {
public:
    Node* dfs(vector<vector<int>>& grid, int r, int c, int n) {
        bool allSame = true;
        int firstVal = grid[r][c];

        // Check if all values in the current grid are the same
        for (int i = r; i < r + n; ++i) {
            for (int j = c; j < c + n; ++j) {
                if (grid[i][j] != firstVal) {
                    allSame = false;
                    break;
                }
            }
            if (!allSame) break;
        }

        // If all values are the same, create a leaf node
        if (allSame) {
            return new Node(firstVal, true);
        }

        // Otherwise, divide the grid into 4 quadrants and recursively process them
        int half = n / 2;
        Node* topLeft = dfs(grid, r, c, half);
        Node* topRight = dfs(grid, r, c + half, half);
        Node* bottomLeft = dfs(grid, r + half, c, half);
        Node* bottomRight = dfs(grid, r + half, c + half, half);

        return new Node(false, false, topLeft, topRight, bottomLeft, bottomRight);
    }

    Node* construct(vector<vector<int>>& grid) {
        int n = grid.size();
        return dfs(grid, 0, 0, n);
    }
};
