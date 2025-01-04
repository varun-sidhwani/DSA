https://leetcode.com/discuss/interview-question/5011090/Google-or-Onsite-or-Balanced-Parentheses-with-Strings-(Unique-Pairing)


#include <stack>
#include <unordered_map>
#include <string>
using namespace std;

bool isValidUnique(const string& s) {
    // Mapping of closing brackets to their corresponding opening brackets
    unordered_map<char, char> bracketMap = {
        {')', '('},
        {'}', '{'},
        {']', '['}
    };

    // Stack to track unmatched opening brackets
    stack<char> bracketStack;

    for (char ch : s) {
        if (bracketMap.count(ch)) {
            // If it's a closing bracket, check for a match
            if (bracketStack.empty() || bracketStack.top() != bracketMap[ch]) {
                return false; // Mismatch or no opening bracket
            }
            bracketStack.pop(); // Valid match
        } else {
            // If it's an opening bracket, push onto the stack
            bracketStack.push(ch);
        }
    }

    // All brackets should be matched if the stack is empty
    return bracketStack.empty();
}
