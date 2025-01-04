https://leetcode.com/discuss/interview-question/5963260/Google-India-Interview-Experience-or-L4-or-phone-screen-or-onsite-or-reject

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const int MOD = 1e9 + 7;

// Recursive function to calculate subsequences starting from index i
int dp(int i, const string& S, vector<int>& memo, unordered_map<char, int>& lastOccurrence) {
    if (i == S.size()) return 1; // Base case: Only the empty subsequence

    if (memo[i] != -1) return memo[i]; // Return cached result if already computed

    // Calculate subsequences including and excluding S[i]
    long long result = (2 * dp(i + 1, S, memo, lastOccurrence)) % MOD;

    // If the current character has appeared before, subtract double-counted subsequences
    if (lastOccurrence.find(S[i]) != lastOccurrence.end()) {
        int j = lastOccurrence[S[i]];
        result = (result - dp(j + 1, S, memo, lastOccurrence) + MOD) % MOD;
    }

    // Update the last occurrence of the current character
    lastOccurrence[S[i]] = i;

    // Store result in memo table
    return memo[i] = result;
}

// Main function to calculate distinct subsequences
int distinctSubsequences(const string& S) {
    int n = S.size();
    vector<int> memo(n, -1); // DP memoization array
    unordered_map<char, int> lastOccurrence; // Tracks the last occurrence of each character

    // Compute total distinct subsequences starting from index 0
    return (dp(0, S, memo, lastOccurrence) - 1 + MOD) % MOD; // Subtract 1 to exclude the empty subsequence
}

int main() {
    string S;
    cin >> S;

    cout << distinctSubsequences(S) << endl;
    return 0;
}
