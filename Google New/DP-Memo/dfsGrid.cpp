https://leetcode.com/discuss/interview-question/6038441/Google-or-L4-or-Phonescreen

Initial Question: Recursive Solution with Memoization

#include <iostream>
#include <vector>

using namespace std;

// Recursive function to calculate paths with memoization
int countPaths(int i, int j, int n, int m, vector<vector<int>>& memo) {
    // Base case: If we reach the bottom-right corner
    if (i == n - 1 && j == m - 1) return 1;

    // Out of bounds
    if (i < 0 || i >= n || j >= m) return 0;

    // If already computed, return the stored value
    if (memo[i][j] != -1) return memo[i][j];

    // Calculate paths by moving right, diagonally up-right, and diagonally down-right
    int right = countPaths(i, j + 1, n, m, memo);          // Move right
    int diagUp = countPaths(i - 1, j + 1, n, m, memo);     // Move diagonally up-right
    int diagDown = countPaths(i + 1, j + 1, n, m, memo);   // Move diagonally down-right

    // Store the result in memo and return
    return memo[i][j] = right + diagUp + diagDown;
}

int main() {
    int n = 3, m = 4; // Example grid size

    // Memoization table initialized with -1
    vector<vector<int>> memo(n, vector<int>(m, -1));

    // Start from the bottom-left corner
    cout << "Total unique paths: " << countPaths(n - 1, 0, n, m, memo) << endl;

    return 0;
}


Follow-Up 1: Recursive Solution with Checkpoints
To incorporate checkpoints, we calculate paths between successive checkpoints recursively. Each segment is solved as a separate problem.

#include <iostream>
#include <vector>
using namespace std;

// Recursive function with memoization
int countPaths(int i, int j, int endX, int endY, int n, int m, vector<vector<int>>& memo) {
    // Base case: If we reach the target checkpoint
    if (i == endX && j == endY) return 1;

    // Out of bounds
    if (i < 0 || i >= n || j >= m) return 0;

    // If already computed, return the stored value
    if (memo[i][j] != -1) return memo[i][j];

    // Calculate paths by moving right, diagonally up-right, and diagonally down-right
    int right = countPaths(i, j + 1, endX, endY, n, m, memo);
    int diagUp = countPaths(i - 1, j + 1, endX, endY, n, m, memo);
    int diagDown = countPaths(i + 1, j + 1, endX, endY, n, m, memo);

    // Store the result in memo and return
    return memo[i][j] = right + diagUp + diagDown;
}

int main() {
    int n = 5, m = 5; // Example grid size
    vector<pair<int, int>> checkpoints = {{3, 2}, {1, 3}};
    int startX = 4, startY = 0;
    int endX = 4, endY = 4;

    int totalPaths = 1;

    pair<int, int> prev = {startX, startY};
    for (auto& cp : checkpoints) {
        vector<vector<int>> memo(n, vector<int>(m, -1));
        totalPaths *= countPaths(prev.first, prev.second, cp.first, cp.second, n, m, memo);
        prev = cp;
    }

    vector<vector<int>> memo(n, vector<int>(m, -1));
    totalPaths *= countPaths(prev.first, prev.second, endX, endY, n, m, memo);

    cout << "Total unique paths with checkpoints: " << totalPaths << endl;
    return 0;
}

Follow-Up 2: Checkpoints in a Specific Order
In Follow-Up 1, we have to cover all the checkpoints, right? If that is true, I believe all the checkpoints will always be visited in a unique order. The order will be the ascending order of the columns of checkpoints. (If two checkpoints are on same column, the answer should be zero.)
So for follow up 2, you will simply check if the specified order matches the unique order. If it does, the answer will be same as that of follow up 1. Otherwise answer should be zero.