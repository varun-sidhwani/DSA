https://leetcode.com/discuss/interview-question/351147/google-onsite-arithmetic-expression-to-construct-a-value

Similar Question - https://leetcode.com/problems/expression-add-operators/description/

https://leetcode.com/discuss/interview-question/4948927/Google-or-SDE2-or-Phone-Screen

// Algorithm

// Create a function generatePossibleResults(a, b), which returns an array of results of all possible mathematical operations on two numbers.

// Create a function checkIfResultReached(list), to check whether we can reach the result 24 using the current array list.

// First, check for base case conditions. If the array size is 1, return true if the result 24, otherwise return false.
// If the array size is greater than 1, we choose any two numbers from the list, perform all mathematical operations on them, create a new list with updated elements and call the recursive function again using this new list. If we don't reach the result 24 using this new list, we backtrack.
// After trying all combinations, if none of them results in 24, return false.
// Call the function we created in step 2 (checkIfResultReached) with the initial cards list in the original problem.



class Solution {
public:
    // Generate all possible results of operations between two numbers.
    vector<double> calculate(double a, double b) {
        vector<double> results = { a + b, a - b, b - a, a * b };
        if (a != 0) results.push_back(b / a);
        if (b != 0) results.push_back(a / b);
        return results;
    }
    
    // Recursively check if we can achieve 24 with the current list of numbers.
    bool canReach24(vector<double>& numbers) {
        // Base Case: If only one number is left, check if it's approximately 24.
        if (numbers.size() == 1) {
            return abs(numbers[0] - 24) <= 0.1;
        }

        // Try all pairs of numbers in the list.
        for (int i = 0; i < numbers.size(); i++) {
            for (int j = i + 1; j < numbers.size(); j++) {
                // Create a new list with the remaining numbers, excluding i and j.
                vector<double> remainingNumbers;
                for (int k = 0; k < numbers.size(); k++) {
                    if (k != i && k != j) {
                        remainingNumbers.push_back(numbers[k]);
                    }
                }
                
                // Perform all possible operations between numbers[i] and numbers[j].
                for (double result : calculate(numbers[i], numbers[j])) {
                    // Add the result of the operation to the new list.
                    remainingNumbers.push_back(result);

                    // Recursively check if we can reach 24 with the new list.
                    if (canReach24(remainingNumbers)) {
                        return true;
                    }

                    // Backtrack: remove the result from the list.
                    remainingNumbers.pop_back();
                }
            }
        }

        // If no combination leads to 24, return false.
        return false;
    }
    
    bool judgePoint24(vector<int>& cards) {
        // Convert the input integers to doubles for precise calculations.
        vector<double> numbers(cards.begin(), cards.end());
        return canReach24(numbers);
    }
};
