// Given an expression with some variables, operands (+ and -) and parenthesis, return the simplified expression.

// Example : a-(a-b)-c
// Output : b-c


// Follow up: 
// What if nested parentheses are allowed?

// Example: a-(b-(c-a)) + c
// Output : -b+2c

// https://leetcode.com/discuss/interview-question/6181749/Google-or-L3-or-Bangalore-Offer

#include <iostream>
#include <unordered_map>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

string simplifyExpression(string expr) {
    stack<int> signs; // Stack to track signs
    signs.push(1);    // Start with global `+`
    int sign = 1;     // Current sign
    unordered_map<char, int> coeff; // Map to store variable coefficients

    for (int i = 0; i < expr.length(); ++i) {
        char ch = expr[i];

        if (ch == '+') {
            sign = signs.top(); // Apply the top sign in the stack
        } else if (ch == '-') {
            sign = -signs.top(); // Flip the top sign in the stack
        } else if (ch == '(') {
            // Push current sign onto the stack
            signs.push(sign);
        } else if (ch == ')') {
            // Pop the stack
            signs.pop();
        } else if (isalpha(ch)) {
            // Handle variables
            coeff[ch] += sign; // Update the coefficient of the variable
        }
    }

    // Build the simplified expression
    string result;
    for (auto& [var, count] : coeff) {
        if (count > 0) {
            if (!result.empty()) result += '+';
            result += (count == 1 ? string(1, var) : to_string(count) + var);
        } else if (count < 0) {
            result += (count == -1 ? "-" + string(1, var) : to_string(count) + var);
        }
    }

    return result.empty() ? "0" : result; // Return "0" if the result is empty
}

int main() {
    string expression = "a-(a-b)-c";
    cout << "Simplified Expression: " << simplifyExpression(expression) << endl;
    return 0;
}
