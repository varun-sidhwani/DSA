https://leetcode.com/problems/reach-end-of-array-with-max-score/description/
https://leetcode.com/discuss/interview-question/4947290/google-phone-maximum-total-score
https://leetcode.com/discuss/interview-question/4978447/Google-coding-interview-experience
This is reverse, here keep track of the maxSoFar on the left
dp[i] = (maxSoFarOnLeft - i ) * nums[maxSoFar] + dp[maxSoFar];

//  from each index i, the optimal solution is to jump to the nearest index j > i such that nums[j] > nums[i].
//  use monotonic stack to find the next greater elements

class Solution {
public:
    long long findMaximumScore(vector<int>& nums) {
        int n = nums.size();
        vector<long long> dp(n, 0);

        dp[n - 1] = 0;
        stack<int> st;
        st.push(n - 1);
        for(int i = n - 2; i >= 0; i--){

            while(!st.empty() && nums[st.top()] <= nums[i])
                st.pop();

            int nextGreater = n - 1;

            if(!st.empty())
                nextGreater = st.top();

            dp[i] = (long long) (nextGreater - i) * nums[i] + dp[nextGreater];

            st.push(i);

        }


        return dp[0];
    }
};