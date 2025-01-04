https://leetcode.com/problems/form-largest-integer-with-digits-that-add-up-to-target/

https://leetcode.com/discuss/interview-question/4878435/Google-Telephonic-PhoneScreen-Interview-question


class Solution {
    public:
    string largestNumber(vector<int>& cost, int target) {
        int n = cost.size();
        vector<vector<string>> dp(n + 1, vector<string>(target + 1, "-1"));
        return dfs(cost, 0, target, dp);
    }
    string dfs(vector<int>& cost, int idx, int target, vector<vector<string>>& dp) {
        if (target == 0) return "";                        // success
        if (target < 0 || idx == cost.size()) return "0";  // failure

        if (dp[idx][target] != "-1") return dp[idx][target];

        string includes = to_string(idx + 1) + dfs(cost, 0, target - cost[idx], dp);
        string excludes = dfs(cost, idx + 1, target, dp);

        return dp[idx][target] = getBigger(includes, excludes);
    }
    string getBigger(string& s1, string& s2) {
    string t = "0";

    // If both s1 and s2 are invalid, return "0"
    if (s1.find(t) != std::string::npos && s2.find(t) != std::string::npos) {
        return "0";
    }

    // If s1 is invalid, return s2 (valid)
    if (s1.find(t) != std::string::npos) return s2;

    // If s2 is invalid, return s1 (valid)
    if (s2.find(t) != std::string::npos) return s1;

    // Compare by length
    if (s1.length() > s2.length())
        return s1;
    else
        return s2;
    }
};