https://leetcode.com/problems/shortest-palindrome/submissions/719105336/

#include <string>
using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        long long prefix = 0;
        long long suffix = 0;
        long long base = 29;
        int last_index = 0; // -1
        long long power = 1;
        long long mod = 1000000007;

        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            int char_val = (c - 'a' + 1);

            prefix = (prefix * base) % mod;
            prefix = (prefix + char_val) % mod;

            suffix = (suffix + char_val * power) % mod;
            power = (power * base) % mod;

            if (prefix == suffix) {
                last_index = i;
            }
        }

        string suffix_part = s.substr(last_index + 1);
        reverse(suffix_part.begin(), suffix_part.end());

        return suffix_part + s;
    }
};
