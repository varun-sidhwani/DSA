https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/editorial/


class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        int res = INT_MAX; // Result to store the minimum length
        long long cur_sum = 0; // Prefix sum
        deque<pair<long long, int>> q; // Monotonic deque (prefix_sum, index)

        for (int r = 0; r < n; ++r) {
            cur_sum += nums[r];

            // Case 1: If the current prefix sum itself satisfies the condition
            if (cur_sum >= k) {
                res = min(res, r + 1);
            }

            // Case 2: Find the minimum valid window ending at `r`
            while (!q.empty() && cur_sum - q.front().first >= k) {
                res = min(res, r - q.front().second);
                q.pop_front();
            }

            // Case 3: Maintain the monotonicity of the deque
            while (!q.empty() && q.back().first >= cur_sum) {
                q.pop_back();
            }

            // Add the current prefix sum and index to the deque
            q.push_back({cur_sum, r});
        }

        return (res == INT_MAX) ? -1 : res;
    }
};