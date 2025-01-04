https://leetcode.com/discuss/interview-question/4314794/GOOGLE-SDE-2-CODING-ROUND-1%3A-Find-the-in-compatible-pair-of-unit-tests/

#include <iostream>
#include <vector>
using namespace std;

// Mock testRunner function
// Replace this with the actual testRunner implementation
bool testRunner(const vector<int>& tests) {
    // Example mock behavior for conflict between 2 and 4
    for (int i = 0; i < tests.size(); ++i) {
        for (int j = i + 1; j < tests.size(); ++j) {
            if ((tests[i] == 2 && tests[j] == 4) || (tests[i] == 4 && tests[j] == 2)) {
                return false; // Fail if 2 and 4 are run together
            }
        }
    }
    return true; // Pass otherwise
}

// Function to find a conflicting pair
pair<int, int> findConflictingPair(vector<int>& tests) {
    // Base case: Only two tests left, check directly
    if (tests.size() == 2) {
        if (!testRunner(tests)) {
            return {tests[0], tests[1]};
        }
        return {-1, -1}; // No conflict
    }

    // Divide the tests into two subsets
    int mid = tests.size() / 2;
    vector<int> subsetA(tests.begin(), tests.begin() + mid);
    vector<int> subsetB(tests.begin() + mid, tests.end());

    // Test each subset individually
    bool resultA = testRunner(subsetA);
    bool resultB = testRunner(subsetB);

    if (!resultA) {
        // Conflict is in subset A
        return findConflictingPair(subsetA);
    } else if (!resultB) {
        // Conflict is in subset B
        return findConflictingPair(subsetB);
    } else {
        // Conflict is split across subsets
        for (int a : subsetA) {
            vector<int> combined = subsetB;
            combined.push_back(a);
            if (!testRunner(combined)) {
                // Conflict is between 'a' and some test in subset B
                for (int b : subsetB) {
                    if (!testRunner({a, b})) {
                        return {a, b};
                    }
                }
            }
        }
    }

    return {-1, -1}; // Should not reach here
}

// Main function for testing
int main() {
    // Example input
    vector<int> tests = {1, 2, 3, 4, 5};

    // Find and print the conflicting pair
    pair<int, int> conflict = findConflictingPair(tests);
    if (conflict.first != -1) {
        cout << "Conflicting Pair: " << conflict.first << " and " << conflict.second << endl;
    } else {
        cout << "No conflicting pair found!" << endl;
    }

    return 0;
}
