
https://leetcode.com/discuss/interview-question/4878831/Google-onsite-question

https://leetcode.com/problems/odd-even-jump/description/


#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

int solve_map(vector<int> &a, int x, int s, int d, vector<vector<int>> &dp, unordered_map<int, set<int>> &mp) {
    int n = a.size();

    // If we've visited this state before, it means we're in a cycle
    if (dp[s][d] == 1) {
        return -1; // Infinite loop detected
    }
    dp[s][d] = 1; // Mark the current state as visited

    // If there are no valid positions to jump to, return the current index
    if (mp.find(a[s] + 1) == mp.end()) {
        return s;
    }

    int next_idx = -1;
    
    // Search for the next valid jump depending on the direction
    if (d == 0) { // Moving left
        for (auto idx : mp[a[s] + 1]) {
            if (idx >= s) {
                break;
            }
            next_idx = idx;
        }
    } else { // Moving right
        for (auto idx : mp[a[s] + 1]) {
            if (idx > s) {
                next_idx = idx;
                break;
            }
        }
    }

    // // If no valid jump is found, return the current index
    // if (next_idx == -1) {
    //     return s;
    // }

    // int next_idx = -1;
    
    // // Search for the next valid jump depending on the direction
    // if (d == 0) { // Moving left
    //     auto it = mp[a[s] + 1].lower_bound(s);
    //     if (it != mp[a[s] + 1].begin()) {
    //         --it; // Move to the largest index less than s
    //         next_idx = *it;
    //     }
    // } else { // Moving right
    //     auto it = mp[a[s] + 1].lower_bound(s + 1);
    //     if (it != mp[a[s] + 1].end()) {
    //         next_idx = *it; // First index greater than s
    //     }
    // }

    // // If no valid jump is found, return the current index
    // if (next_idx == -1) {
    //     return s;
    // }

    // Update the map and array with the new value at the current position
    mp[a[s] + x].insert(s);
    mp[a[s]].erase(s);
    a[s] += x; // Update the value at the current index by adding X

    // Recursively call solve_map with the new position and the opposite direction
    return solve_map(a, x, next_idx, 1 - d, dp, mp);
}

int main() {
    vector<int> a = {3, 4, 2, 2, 7};
    int x = 4;
    int s = 2; // Starting index

    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(2, 0)); // DP table to track visited states

    // Initialize the map with the indices of each value in the array
    unordered_map<int, set<int>> mp;
    for (int i = 0; i < n; ++i) {
        mp[a[i]].insert(i);
    }

    // Solve the problem using the optimized approach
    int result = solve_map(a, x, s, 0, dp, mp); // Start with direction 0 (left)

    cout << "Final position: " << result << endl;
    return 0;
}
