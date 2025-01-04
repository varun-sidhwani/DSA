/*
You are given a number (very long) and an integer K. Find the largest K-digit number that can be formed
from the original number (preserve the order). 

Example : S = "3582",   K=2
Output: "82"

Follow up 1: Solve in O(n) time
Follow up 2: Solve in O(n) time and O(k) space

*/

#include <iostream>
#include <string>
#include <stack>
using namespace std;

string largestKDigitNumber(string S, int K) {
    stack<char> st;
    int n = S.length();

    for (int i = 0; i < n; i++) {
        // While the stack is not empty, and the current digit is greater than the top of the stack,
        // and there are enough digits left to form a K-digit number
        while (!st.empty() && st.top() < S[i] && st.size() + (n - i - 1) >= K) {
            st.pop();
        }
        st.push(S[i]);
    }

    // If the stack has more than K digits, truncate it
    string result = "";
    while (!st.empty()) {
        result = st.top() + result;
        st.pop();
    }

    return result.substr(0, K); // Take only the first K digits
}

int main() {
    string S = "3582";
    int K = 2;
    cout << "Largest " << K << "-digit number: " << largestKDigitNumber(S, K) << endl;

    return 0;
}
