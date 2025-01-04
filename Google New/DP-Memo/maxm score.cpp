https://leetcode.com/discuss/interview-question/5955653/Google-Screening-question-2024-or-L4-or-Bangalore-India-or-Reject

// Global variables
vector<int> sequence;
int threshold, totalParts;
int dp[1001][1001]; // Memo table for (i, parts)

// Helper function to calculate max score
int maxScore(int i, int parts) {
    // Base cases
    if (parts == totalParts) return 0; // Cannot form more parts
    if (i == sequence.size()) return 0; // No more elements to form subsequences

    // If already computed, return the memoized result
    if (dp[i][parts] != -1) return dp[i][parts];

    int sum = 0, result = 0;
    // Try forming a new subsequence starting at index i
    for (int j = i; j < sequence.size(); j++) {
        sum += sequence[j];
        if (sum >= threshold) {
            result = max(result, 1 + maxScore(j + 1, parts + 1));
        } else {
            result = max(result, maxScore(j + 1, parts + 1));
        }
    }

    // Memoize and return the result
    return dp[i][parts] = result;
}

int main() {
    // Example input
    sequence = {1, 4, 2, 8};
    int parts = 3, thresholdInput = 9;
    totalParts = parts;
    threshold = thresholdInput;

    // Initialize DP table with -1
    memset(dp, -1, sizeof(dp));

    // Compute the maximum score starting from index 0 and 0 parts formed
    int result = maxScore(0, 0);
    cout << "Maximum Score: " << result << endl;

    return 0;
}
