https://leetcode.com/discuss/interview-question/6082922/Google-online-interview-question

using namespace std;

// Memoization key generator
string makeKey(int idx, int currentSum) {
    return to_string(idx) + "|" + to_string(currentSum);
}

// Recursive function with memoization to find all subsets
vector<vector<string>> findSubsetsMemo(int idx, int currentSum, int target,
                                       vector<int>& votePowers, vector<string>& states,
                                       unordered_map<string, vector<vector<string>>>& memo) {
    if (currentSum == target) {
        return {{}};
    }

    if (idx >= votePowers.size() || currentSum > target) {
        return {};
    }

    string key = makeKey(idx, currentSum);

    // Check memoized results
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    vector<vector<string>> subsets;

    // Include the current state
    auto includeSubsets = findSubsetsMemo(idx + 1, currentSum + votePowers[idx], target, votePowers, states, memo);
    for (auto& subset : includeSubsets) {
        subset.push_back(states[idx]);
        subsets.push_back(subset);
    }

    // Exclude the current state
    auto excludeSubsets = findSubsetsMemo(idx + 1, currentSum, target, votePowers, states, memo);
    subsets.insert(subsets.end(), excludeSubsets.begin(), excludeSubsets.end());

    // Store the result in memo
    memo[key] = subsets;

    return subsets;
}

// Main function to find all valid splits
vector<vector<vector<string>>> findEqualVoteSplits(vector<int>& votePowers, vector<string>& states) {
    int totalSum = accumulate(votePowers.begin(), votePowers.end(), 0);

    // If total sum is odd, equal split is impossible
    if (totalSum % 2 != 0) {
        return {};
    }

    int target = totalSum / 2;
    unordered_map<string, vector<vector<string>>> memo;

    // Find all subsets with sum = target
    auto subsets = findSubsetsMemo(0, 0, target, votePowers, states, memo);

    // Use a set to avoid duplicate splits
    set<pair<vector<string>, vector<string>>> uniqueSplits;

    // Generate complement subsets for each found subset
    for (const auto& subset : subsets) {
        vector<string> complement;
        vector<bool> used(states.size(), false);

        // Mark the states in the current subset
        for (const auto& state : subset) {
            auto it = find(states.begin(), states.end(), state);
            if (it != states.end()) {
                used[it - states.begin()] = true;
            }
        }

        // Build the complement
        for (int i = 0; i < states.size(); i++) {
            if (!used[i]) {
                complement.push_back(states[i]);
            }
        }

        // Sort subset and complement for consistency
        vector<string> sortedSubset = subset;
        vector<string> sortedComplement = complement;
        sort(sortedSubset.begin(), sortedSubset.end());
        sort(sortedComplement.begin(), sortedComplement.end());

        // Add the pair to the set
        uniqueSplits.insert({sortedSubset, sortedComplement});
    }

    // Convert the set into the result format
    vector<vector<vector<string>>> results;
    for (const auto& split : uniqueSplits) {
        results.push_back({split.first, split.second});
    }

    return results;
}

int main() {
    vector<int> votePowers = {1, 5, 7, 8, 9, 10, 20};
    vector<string> states = {"California", "Texas", "Florida", "Indiana", "Alaska", "Ohio", "Hawaii"};

    auto solutions = findEqualVoteSplits(votePowers, states);

    // Print the results
    if (solutions.empty()) {
        cout << "No equal split is possible!" << endl;
    } else {
        for (const auto& split : solutions) {
            cout << "[";
            for (size_t i = 0; i < split[0].size(); i++) {
                if (i > 0) cout << ", ";
                cout << split[0][i];
            }
            cout << "] and [";
            for (size_t i = 0; i < split[1].size(); i++) {
                if (i > 0) cout << ", ";
                cout << split[1][i];
            }
            cout << "]" << endl;
        }
    }

    return 0;
}
