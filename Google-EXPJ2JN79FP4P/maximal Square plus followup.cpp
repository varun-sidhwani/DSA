
 I was given a binary matrix and asked to find the upper-left corner of the largest square of 1's. 
 The follow-up question was: What if we are allowed to switch at most k zeros to 1's?

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

/**
 * Checks if there exists a square of side 's' in the matrix (using prefix sums)
 * that contains at most 'k' zeros.
 *
 * prefix: 2D prefix sum array of zeros
 * s:      current square side
 * k:      max zeros allowed to flip
 * n, m:   dimensions of the matrix
 */
bool canFindSquareOfSize(const vector<vector<int>>& prefix, int s, int k, int n, int m) {
    // We check all possible positions where an s x s square can fit.
    for (int i = s; i <= n; i++) {
        for (int j = s; j <= m; j++) {
            // Number of zeros in the submatrix with bottom-right corner at (i, j)
            // and top-left corner at (i - s + 1, j - s + 1) in 1-based indexing.
            int zeros = prefix[i][j]
                      - prefix[i - s][j]
                      - prefix[i][j - s]
                      + prefix[i - s][j - s];
            if (zeros <= k) {
                return true;  // Found at least one valid square of side s
            }
        }
    }
    return false;  // No valid square of side s
}

/**
 * Returns a pair consisting of:
 *  1) largest square side length
 *  2) (row, col) of the top-left corner of that square
 *     in 0-based coordinates
 */
pair<int, pair<int,int>> largestSquareWithKSwitchesBinarySearch(const vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    int m = matrix[0].size();

    // 1. Compute prefix sum of zeros
    //    prefix[i][j] = count of zeros in submatrix (0,0) to (i-1,j-1)
    vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            prefix[i][j] = (matrix[i - 1][j - 1] == 0)
                         + prefix[i - 1][j]
                         + prefix[i][j - 1]
                         - prefix[i - 1][j - 1];
        }
    }

    // 2. Binary search for the maximum valid square side
    int low = 1, high = min(n, m);
    int bestSize = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (canFindSquareOfSize(prefix, mid, k, n, m)) {
            bestSize = mid;   // mid is a valid size
            low = mid + 1;    // Try a bigger size
        } else {
            high = mid - 1;   // Try a smaller size
        }
    }

    // 3. (Optional) Find the top-left corner for the 'bestSize' square
    //    We'll do one pass to identify where that square occurs.
    pair<int,int> bestCorner = {-1, -1};
    if (bestSize > 0) {
        // Re-check squares of size 'bestSize' to find the first valid one
        for (int i = bestSize; i <= n; i++) {
            bool found = false;
            for (int j = bestSize; j <= m; j++) {
                int zeros = prefix[i][j]
                          - prefix[i - bestSize][j]
                          - prefix[i][j - bestSize]
                          + prefix[i - bestSize][j - bestSize];
                if (zeros <= k) {
                    // Found the top-left corner in 1-based indexing:
                    //  it is (i - bestSize, j - bestSize) in 1-based
                    //  convert to 0-based by subtracting 1 more
                    bestCorner = { (i - bestSize), (j - bestSize) };
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
    }

    return { bestSize, bestCorner };
}

int main() {
    // Example matrix
    vector<vector<int>> matrix = {
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 1},
        {1, 1, 1, 0}
    };
    int k = 2; // Number of zeros allowed to flip

    auto result = largestSquareWithKSwitchesBinarySearch(matrix, k);
    int largestSide = result.first;
    pair<int,int> corner = result.second;

    cout << "Largest square side: " << largestSide << endl;
    if (largestSide > 0) {
        cout << "Top-left corner (0-based): (" 
             << corner.first << ", " << corner.second << ")\n";
    } else {
        cout << "No valid square found.\n";
    }

    return 0;
}


O(n2log(n2));

