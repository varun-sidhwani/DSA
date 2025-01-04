https://leetcode.com/problems/evaluate-reverse-polish-notation/


class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        int res = 0;
        
        for(int i = 0; i<tokens.size(); i++){
            if(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/"){
                int a = s.top();
                s.pop();
                int b = s.top();
                s.pop();
                int subres;
                if(tokens[i] == "+")
                    subres = a + b;
                else if(tokens[i] == "-")
                    subres = b - a;
                else if(tokens[i] == "*")
                    subres = a * b;
                else{
                    if( (a > 0 && b > 0) || (a < 0 && b < 0))
                        subres = b / a;
                    else
                        subres = ceil( (b * 1.0) / a);// to round towards 0 // -3/2 -> -1.5 -> -2
                }
                s.push(subres);
            }
            else
                s.push(stoi(tokens[i]));
        }
        return s.top();
    }
};