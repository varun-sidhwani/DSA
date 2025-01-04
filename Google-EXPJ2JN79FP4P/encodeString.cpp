https://leetcode.com/problems/encode-string-with-shortest-length/description/


class Solution {
public:
    string encode(string s) {
        unordered_map<string, string> memo;  // To store already computed encodings
        
        // Helper function to encode the substring
        return encode1(s, memo);
    }
    
private:
    string encode1(string str, unordered_map<string, string>& memo) {
        // If the result for this string is already computed, return it
        if (memo.find(str) != memo.end()) {
            return memo[str];
        }
        
        int n = str.size();
        string result = str;  // Default: no encoding, just return the string itself
        
        // Try every possible partition of the string
        for (int len = 1; len <= n / 2; ++len) {
            if (n % len == 0) {
                string sub = str.substr(0, len);
                int count = n / len;
                
                // Check if the substring repeats
                string encoded = sub;
                for (int i = 1; i < count; ++i) {
                    encoded += sub;
                }
                
                if (encoded == str) {
                    // We can encode the string as count[sub]
                    string encodedForm = to_string(count) + "[" + encode1(sub, memo) + "]";
                    if (encodedForm.size() < result.size()) {
                        result = encodedForm;
                    }
                }
            }
        }

        // Check for smaller patterns within the string (recursive approach)
        for (int i = 1; i < n; ++i) {
            string left = str.substr(0, i);
            string right = str.substr(i);
            string encodedLeft = encode1(left, memo);
            string encodedRight = encode1(right, memo);
            string combined = encodedLeft + encodedRight;
            
            if (combined.size() < result.size()) {
                result = combined;
            }
        }
        
        memo[str] = result;  // Store the result in memoization table
        return result;
    }
};
