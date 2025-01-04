https://leetcode.com/problems/odd-even-jump/description/

Also see this question for lower and upper bound.

O(n)×O(logn)=O(nlogn)

class Solution {
public:
    int oddEvenJumps(vector<int>& nums) {
        int n = nums.size();
        vector<bool> dpOdd(n, false), dpEven(n, false);
        dpOdd[n - 1] = true;
        dpEven[n - 1] = true;
        int res = 1; // The last index is always a good starting index
        map<int, int> m; // Stores value -> index
        m[nums[n - 1]] = n - 1;

        for (int i = n - 2; i >= 0; i--) {
            // Odd jump: find smallest key >= nums[i]
            auto pos1 = m.lower_bound(nums[i]);
            if (pos1 != m.end()) {
                dpOdd[i] = dpEven[pos1->second];
            }

            // Even jump: find largest key <= nums[i]
            auto pos2 = m.upper_bound(nums[i]);
            if (pos2 != m.begin()) {
                --pos2; // Move to the largest key <= nums[i]
                dpEven[i] = dpOdd[pos2->second];
            }

            // Update the result
            if (dpOdd[i]) {
                res += 1;
            }

            // Add current value to the map
            m[nums[i]] = i;
        }

        return res;
    }
};
