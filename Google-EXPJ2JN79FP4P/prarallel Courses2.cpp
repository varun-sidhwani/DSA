bitmasking - https://chatgpt.com/share/676fd90d-9cfc-8003-8b4e-8a1d4c358389


#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
using namespace std;

int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
    // Build graph and prerequisites mask
    vector<int> prerequisites(n, 0);
    for (const auto& relation : relations) {
        int prev = relation[0] - 1;
        int next = relation[1] - 1;
        prerequisites[next] |= (1 << prev);
    }

    // DP array to store minimum semesters for each state
    vector<int> dp(1 << n, INT_MAX);
    dp[0] = 0; // No courses taken requires 0 semesters

    // BFS queue
    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int state = q.front();
        q.pop();

        // Identify all courses that can be taken in the current state
        vector<int> availableCourses;
        for (int i = 0; i < n; ++i) {
            if (!(state & (1 << i)) && (state & prerequisites[i]) == prerequisites[i]) {
                availableCourses.push_back(i);
            }
        }

        // Generate all subsets of availableCourses that have size <= k
        int m = availableCourses.size();
        for (int subset = 1; subset < (1 << m); ++subset) {
            if (__builtin_popcount(subset) > k) continue;

            // Compute the new state after taking this subset
            int newState = state;
            for (int j = 0; j < m; ++j) {
                if (subset & (1 << j)) {
                    newState |= (1 << availableCourses[j]);
                }
            }

            // Update DP and push new state to the queue
            if (dp[newState] > dp[state] + 1) {
                dp[newState] = dp[state] + 1;
                q.push(newState);
            }
        }
    }

    // Return the minimum semesters for the final state
    return dp[(1 << n) - 1];
}
