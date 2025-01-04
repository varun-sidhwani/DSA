https://leetcode.com/discuss/interview-question/6035505/Google-India-or-Onsite-Question

#include <iostream>
#include <vector>
#include <algorithm> // for lower_bound and upper_bound

int maxFrequency(const std::vector<int>& arr) {
    int n = arr.size();
    int maxFreq = 0;
    
    for (int i = 0; i < n; ) {
        int current = arr[i];
        // Find the range of current element
        auto lower = std::lower_bound(arr.begin(), arr.end(), current);
        auto upper = std::upper_bound(arr.begin(), arr.end(), current);
        int frequency = upper - lower;
        maxFreq = std::max(maxFreq, frequency);
        // Move to the next unique element
        i += frequency;
    }
    
    return maxFreq;
}

int main() {
    std::vector<int> arr = {1, 2, 2, 3, 3, 3, 3, 4, 4, 5, 6};
    std::cout << "Maximum Frequency: " << maxFrequency(arr) << std::endl;
    return 0;
}
