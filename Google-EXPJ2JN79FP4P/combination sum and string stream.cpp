
https://leetcode.com/discuss/interview-question/4799918/Interview-Experience

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
using namespace std;

// Function to count the maximum frequency of any character in a word
int maxRepeatingChars(const string& word) {
    unordered_map<char, int> freq;
    int maxFreq = 0;

    for (char ch : word) {
        freq[ch]++;
        maxFreq = max(maxFreq, freq[ch]);
    }

    return maxFreq;
}

// Function to find the first word with the most repeating characters
string findWordWithMostRepeats(const string& sentence) {
    stringstream ss(sentence);
    string word, result;
    int maxRepeats = 0;

    while (ss >> word) {
        int currentRepeats = maxRepeatingChars(word);

        // Update the result if this word has more repeats or appears earlier
        if (currentRepeats > maxRepeats) {
            maxRepeats = currentRepeats;
            result = word;
        }
    }

    return result;
}

int main() {
    string sentence = "Today is the greatest day ever!";
    string result = findWordWithMostRepeats(sentence);
    cout << "The word with the most repeating characters is: " << result << endl;
    return 0;
}
