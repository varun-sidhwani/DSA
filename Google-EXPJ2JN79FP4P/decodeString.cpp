class Solution {
public:
    string decodeString(string s) {
        stack<char> stack;
        
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == ']') {
                string decodedStr = "";
                
                // Collect characters for the decoded string (inside the brackets)
                while (stack.top() != '[') {
                    decodedStr = stack.top() + decodedStr;  // Reverse the order while collecting
                    stack.pop();
                }
                stack.pop();  // Remove the '[' from the stack
                
                int k = 0;
                int multiplier = 1;
                
                // Collect the multiplier (k) before the string
                while (!stack.empty() && isdigit(stack.top())) {
                    k = k + (stack.top() - '0') * multiplier;
                    stack.pop();
                    multiplier *= 10;
                }
                
                // Push the decoded string k times onto the stack
                for (int i = 0; i < k; ++i) {
                    for (int j = 0; j < decodedStr.size(); ++j) {
                        stack.push(decodedStr[j]);
                    }
                }
            }
            else {
                // Push current character onto the stack
                stack.push(s[i]);
            }
        }
        
        // Build the final result from the stack
        string result = "";
        while (!stack.empty()) {
            result = stack.top() + result;
            stack.pop();
        }
        
        return result;
    }
};
