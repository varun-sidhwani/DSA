https://leetcode.com/discuss/interview-question/1757185/Google-or-Onsite-or-Merge-two-Screenshots

const int BASE = 26; // Base for the hash

// Compute hash for a single string
long long computeHash(const string &line) {
    long long hash = 0;
    for (char c : line) {
        hash = hash * BASE + (c - 'A' + 1); // Adjust to make 'A' = 1
    }
    return hash;
}

// Merge screenshots using concatenated hashes for comparison
vector<string> mergeScreenshots(const vector<string> &screenshot1, const vector<string> &screenshot2) {
    int n = screenshot1.size();

    // Step 1: Compute hashes for each line
    vector<long long> hash1(n), hash2(n);
    for (int i = 0; i < n; i++) {
        hash1[i] = computeHash(screenshot1[i]);
        hash2[i] = computeHash(screenshot2[i]);
    }

    // Step 2: Binary search for the largest overlap
    int bestOverlap = 0;
    int left = 0, right = n;

    while (left <= right) {
        int mid = (left + right) / 2;

        // Construct concatenated hash strings
        ostringstream suffixHash, prefixHash;

        // Suffix of screenshot1: [n-mid..n-1]
        for (int i = n - mid; i < n; i++) {
            suffixHash << hash1[i] << "-";
        }

        // Prefix of screenshot2: [0..mid-1]
        for (int i = 0; i < mid; i++) {
            prefixHash << hash2[i] << "-";
        }

        if (suffixHash.str() == prefixHash.str()) {
            bestOverlap = mid; // Found a valid overlap
            left = mid + 1;    // Try for a larger overlap
        } else {
            right = mid - 1;   // Try for a smaller overlap
        }
    }

    // Step 3: Merge screenshots based on the overlap
    vector<string> merged;
    for (const auto &line : screenshot1) {
        merged.push_back(line);
    }
    for (int i = bestOverlap; i < n; i++) {
        merged.push_back(screenshot2[i]);
    }

    return merged;
}

// Main function to test the merge
int main() {
    {
        // Example 1
        vector<string> screenshot1 = {"AAA", "BBB", "CCC"};
        vector<string> screenshot2 = {"BBB", "CCC", "DDD"};

        auto merged = mergeScreenshots(screenshot1, screenshot2);

        cout << "Merged Document 1:\n";
        for (const auto &line : merged) {
            cout << line << "\n";
        }
        // Expected: AAA, BBB, CCC, DDD
    }

    cout << "\n";

    {
        // Example 2
        vector<string> screenshot1 = {"AAA", "BBB"};
        vector<string> screenshot2 = {"CCC", "DDD"};

        auto merged = mergeScreenshots(screenshot1, screenshot2);

        cout << "Merged Document 2:\n";
        for (const auto &line : merged) {
            cout << line << "\n";
        }
        // Expected: AAA, BBB, CCC, DDD
    }

    return 0;
}
