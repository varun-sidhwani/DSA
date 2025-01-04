
// Get all sequences that sum to a particular number if digits 1 & 2 can be used.

// Example : Sum=4 
// Result : [“1111”, “112”, “121”, “211”, “22”]

// Follow up 1: What if we are allowed to use first K digits. (1,2,3,...,K)


Code for Digits 1 to 2
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void generateSequences(int target, int currentSum, string currentSequence, vector<string>& results) {
    // Base case: If the current sum equals the target, store the sequence
    if (currentSum == target) {
        results.push_back(currentSequence);
        return;
    }

    // Add digits 1 and 2 if they don't exceed the target
    if (currentSum + 1 <= target) {
        generateSequences(target, currentSum + 1, currentSequence + "1", results);
    }
    if (currentSum + 2 <= target) {
        generateSequences(target, currentSum + 2, currentSequence + "2", results);
    }
}

vector<string> findSequences(int target) {
    vector<string> results;
    generateSequences(target, 0, "", results);
    return results;
}

int main() {
    int target = 4;
    vector<string> sequences = findSequences(target);

    cout << "Sequences summing to " << target << " are:\n";
    for (const string& seq : sequences) {
        cout << seq << endl;
    }

    return 0;
}




// Code for Digits 1 to 𝐾


#include <iostream>
#include <vector>
#include <string>
using namespace std;

void generateSequencesK(int target, int currentSum, string currentSequence, vector<string>& results, int K) {
    // Base case: If the current sum equals the target, store the sequence
    if (currentSum == target) {
        results.push_back(currentSequence);
        return;
    }

    // Add digits from 1 to K if they don't exceed the target
    for (int digit = 1; digit <= K; digit++) {
        if (currentSum + digit <= target) {
            generateSequencesK(target, currentSum + digit, currentSequence + to_string(digit), results, K);
        }
    }
}

vector<string> findSequencesK(int target, int K) {
    vector<string> results;
    generateSequencesK(target, 0, "", results, K);
    return results;
}

int main() {
    int target = 4;
    int K = 3; // Use digits 1, 2, and 3
    vector<string> sequences = findSequencesK(target, K);

    cout << "Sequences summing to " << target << " using digits 1 to " << K << " are:\n";
    for (const string& seq : sequences) {
        cout << seq << endl;
    }

    return 0;
}



// What if we have to only count the number of sequences for the original question?

#include <iostream>
using namespace std;

int countSequences(int N) {
    if (N == 0) return 1; // Base case
    if (N == 1) return 1; // Base case

    int prev2 = 1; // dp[0]
    int prev1 = 1; // dp[1]
    int current = 0;

    for (int i = 2; i <= N; i++) {
        current = prev1 + prev2; // dp[i] = dp[i-1] + dp[i-2]
        prev2 = prev1;
        prev1 = current;
    }

    return current; // dp[N]
}

int main() {
    int N = 4;
    cout << "Number of sequences summing to " << N << " is: " << countSequences(N) << endl;
    return 0;
}


// Follow up 3: Count the number of sequences when K digits are allowed


#include <iostream>
#include <vector>
using namespace std;

int countSequences(int N, int K) {
    if (N == 0) return 1; // Base case
    if (K == 0) return 0; // No valid sequences if no digits are allowed

    vector<int> dp(N + 1, 0);
    dp[0] = 1; // Base case: one way to sum to 0 (empty sequence)

    int windowSum = dp[0]; // Sliding window sum for the last K values

    for (int i = 1; i <= N; i++) {
        dp[i] = windowSum; // Start with the sum of the last K values
        if (i - K >= 0) {
            windowSum -= dp[i - K]; // Remove the value that goes out of the window
        }
        windowSum += dp[i]; // Add the current value to the window
    }

    return dp[N];
}

int main() {
    int N = 4, K = 2;
    cout << "Number of sequences summing to " << N << " using digits 1 to " << K << " is: " << countSequences(N, K) << endl;
    return 0;
}
