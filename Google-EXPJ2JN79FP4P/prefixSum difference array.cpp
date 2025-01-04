/*

Question 1:
You are given an array of length n and q queries. Each query consists of two indices [l, r], representing a subarray from index l to r (both inclusive). For each query, we are allowed to subtract 1 from any subsequence within the range [l, r]. After processing all the queries, determine whether it's possible to make all elements of the array equal to zero.


Example:
arr = [1, 2, 3]
queries = [[0, 1], [1, 2], [0, 2], [1, 2]]


Output: true


Explanation:
query --> arr -- subsequence
[0, 1] --> [0, 1, 3] -- {1, 2}
[1, 2] --> [0, 0, 2] -- {1 , 3}
[0, 2] --> [0, 0, 1] -- {2}
[1, 2] --> [0, 0, 0] -- {1}


*/


#include <iostream>
#include <vector>
using namespace std;

bool canMakeAllZero(vector<int>& arr, vector<vector<int>>& queries) {
    int n = arr.size();
    vector<int> diff(n + 1, 0);

    // Build the difference array for the queries
    for (const auto& query : queries) {
        int l = query[0], r = query[1];
        diff[l] += 1;
        if (r + 1 < n) {
            diff[r + 1] -= 1;
        }
    }

    // Calculate the cumulative sum to get the total operations for each index
    vector<int> operations(n, 0);
    operations[0] = diff[0];
    for (int i = 1; i < n; i++) {
        operations[i] = operations[i - 1] + diff[i];
    }

    // Check if each element can be reduced to zero
    for (int i = 0; i < n; i++) {
        if (operations[i] < arr[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    vector<int> arr = {1, 2, 3};
    vector<vector<int>> queries = {{0, 1}, {1, 2}, {0, 2}, {1, 2}};
    if (canMakeAllZero(arr, queries)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    return 0;
}
