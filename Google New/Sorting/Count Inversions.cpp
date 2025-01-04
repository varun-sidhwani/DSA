https://leetcode.com/discuss/interview-question/6072729/Google-Interview-Coding-question

Number of swaps required is equal to the count of inversions in the indices array.
inversion - when i < j but indices[i] > indices[j];
We're basically trying to sort the array.
Sorting an array is basically fixing the inversions.

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Merge function to count inversions
int mergeAndCount(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0, inversions = 0;

    // Merge and count inversions
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inversions += (mid - i + 1); // Count inversions
        }
    }

    // Copy remaining elements
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    // Copy back to the original array
    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }

    return inversions;
}

// Recursive function to count inversions
int mergeSortAndCount(vector<int>& arr, int left, int right) {
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    int inversions = 0;

    inversions += mergeSortAndCount(arr, left, mid);
    inversions += mergeSortAndCount(arr, mid + 1, right);
    inversions += mergeAndCount(arr, left, mid, right);

    return inversions;
}

// Function to calculate the minimum contiguous swaps
int minSwaps(vector<string>& source, vector<string>& target) {
    unordered_map<string, int> positionMap;

    // Map the target element positions for quick lookup
    for (int i = 0; i < target.size(); i++) {
        positionMap[target[i]] = i;
    }

    // Create a permutation of indices according to the target order
    vector<int> indices;
    for (const auto& element : source) {
        indices.push_back(positionMap[element]);
    }

    // Count inversions in the indices array
    return mergeSortAndCount(indices, 0, indices.size() - 1);
}

int main() {
    vector<string> source = {"B", "C", "A", "D"};
    vector<string> target = {"C", "D", "A", "B"};

    int result = minSwaps(source, target);

    cout << "Minimum contiguous swaps required: " << result << endl;

    return 0;
}
