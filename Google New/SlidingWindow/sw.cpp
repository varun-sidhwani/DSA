
https://leetcode.com/discuss/interview-question/6038274/Google-or-Phone-Screen-or-L3


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to find maximum non-decreasing subarray length
int findMaxNonDecreasingLength(const vector<int>& arr) {
    int n = arr.size();
    int maxLength = 1, start = 0;

    for (int end = 1; end < n; ++end) {
        if (arr[end] < arr[end - 1]) {
            start = end; // Reset window start
        }
        maxLength = max(maxLength, end - start + 1);
    }

    return maxLength;
}

// Function to find maximum length after one change
int findMaxLengthAfterChange(const vector<int>& arr) {
    int n = arr.size();
    int maxLength = 1, start = 0, lastBreak = -1;

    for (int end = 1; end < n; ++end) {
        if (arr[end] < arr[end - 1]) {
            if (lastBreak != -1) {
                // If a second violation occurs, move the window start
                start = lastBreak + 1;
            }
            lastBreak = end - 1; // Update last violation index
        }

        // Calculate the maximum length, considering one change
        maxLength = max(maxLength, end - start + 1);
    }

    return maxLength;
}

int main() {
    vector<int> arr = {1, 3, 5, 4, 6, 8, 2, 10};

    // Part 1: Find maximum length of non-decreasing subarray
    cout << "Maximum length of non-decreasing subarray: "
         << findMaxNonDecreasingLength(arr) << endl;

    // Part 2: Find maximum length after one change
    cout << "Maximum length after one change: "
         << findMaxLengthAfterChange(arr) << endl;

    return 0;
}
