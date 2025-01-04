// Validate if the equation is syntactically correct.

// Valid operators: +, -, a-z, (, )
// Test cases:
// Valid - a + x = b + (c + a)
// Invalid - a + x = (ending with =; doesn't have RHS)
// Invalid - a + -x = a + b (- in -x is a unary operator)


#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

bool isValidEquation(const string& equation) {
    // Step 1: Split the equation into LHS and RHS
    size_t equalPos = equation.find('=');
    if (equalPos == string::npos) return false; // No '=' in the equation
    string lhs = equation.substr(0, equalPos);
    string rhs = equation.substr(equalPos + 1);

    // Both LHS and RHS must be non-empty
    if (lhs.empty() || rhs.empty()) return false;

    // Helper function to validate one side of the equation
    auto isValidSide = [](const string& side) {
        stack<char> parentheses;
        bool expectOperand = true; // Start expecting an operand

        for (size_t i = 0; i < side.size(); ++i) {
            char c = side[i];

            if (isalpha(c)) { // Variable (a-z)
                if (!expectOperand) return false; // Misplaced variable
                expectOperand = false; // Next, expect an operator
            } else if (c == '+' || c == '-') { // Operator
                if (expectOperand) return false; // Misplaced operator
                expectOperand = true; // Next, expect an operand
            } else if (c == '(') { // Open parenthesis
                if (!expectOperand) return false; // Misplaced '('
                parentheses.push(c);
                expectOperand = true; // Expect operand inside parentheses
            } else if (c == ')') { // Close parenthesis
                if (expectOperand) return false; // Misplaced ')'
                if (parentheses.empty() || parentheses.top() != '(') return false; // Unmatched ')'
                parentheses.pop();
                expectOperand = false; // Next, expect an operator
            } else {
                return false; // Invalid character
            }
        }

        // Ensure all parentheses are closed and no dangling operators
        return parentheses.empty() && !expectOperand;
    };

    // Validate both sides
    return isValidSide(lhs) && isValidSide(rhs);
}

// Test the function
int main() {
    string test1 = "a + x = b + (c + a)"; // Valid
    string test2 = "a + x =";            // Invalid (no RHS)
    string test3 = "a + -x = a + b";     // Invalid (unary '-')

    cout << (isValidEquation(test1) ? "Valid" : "Invalid") << endl;
    cout << (isValidEquation(test2) ? "Valid" : "Invalid") << endl;
    cout << (isValidEquation(test3) ? "Valid" : "Invalid") << endl;

    return 0;
}
