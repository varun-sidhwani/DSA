
https://leetcode.com/discuss/interview-question/6049364/GoogleorL4orPhone-Screen-Round

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Function to expand placeholders in a string
string expandPlaceholders(string text, unordered_map<string, string>& templateMap, unordered_map<string, string>& memo, unordered_set<string>& visiting) {
    size_t start = 0;
    while ((start = text.find('%', start)) != string::npos) {
        size_t end = text.find('%', start + 1);
        if (end == string::npos) break; // No closing '%'

        string key = text.substr(start + 1, end - start - 1);

        if (visiting.count(key)) throw runtime_error("Cyclic dependency detected!"); // Detect cycles
        if (!templateMap.count(key)) { // Skip unknown placeholders
            start = end + 1;
            continue;
        }

        // Resolve the placeholder recursively
        visiting.insert(key); // Mark as visiting
        string resolvedValue = memo.count(key) ? memo[key] : expandPlaceholders(templateMap[key], templateMap, memo, visiting);
        visiting.erase(key); // Mark as resolved

        // Cache the resolved value
        memo[key] = resolvedValue;

        // Replace the placeholder in the text
        text.replace(start, end - start + 1, resolvedValue);
        start += resolvedValue.length(); // Move past the resolved value
    }
    return text;
}

int main() {
    // Template map
    unordered_map<string, string> templateMap = {
        {"X", "123"},
        {"Y", "456_%X%"},
        {"Z", "%Y%_%X%_789"}
    };

    unordered_map<string, string> memo; // Memoization map
    unordered_set<string> visiting;    // Detect cyclic dependencies

    // Resolve all placeholders in the template map
    for (auto& pair : templateMap) {
        pair.second = expandPlaceholders(pair.second, templateMap, memo, visiting);
    }

    // Input string
    string input = "%Z%";

    // Resolve placeholders in the input string
    string output = expandPlaceholders(input, templateMap, memo, visiting);

    // Print the result
    cout << "Output: " << output << endl;

    return 0;
}
