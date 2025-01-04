
https://leetcode.com/discuss/interview-question/4834179/Google-L4-or-Onsite

https://chatgpt.com/share/676e612b-33c8-8003-994b-089f096df7bb


O(KlogN)

K = number of 1's and N = size of array
sice k <<<< N

can be considered logN


#include <vector>
#include <iostream>
using namespace std;

#define INF 1000000000 // Assuming INF is a large number larger than any possible index

vector<int> positions_of_ones;

// Simulated API call (you will replace this with the actual database API)
bool api_call(int left, int right) {
    // This is just a placeholder for the actual query.
    // Return true if there's at least one 1 bit in the range [left..right], false otherwise.
    // Example:
    // if the bit array is {0, 1, 0, 0, 1}, query(1, 3) should return true, query(4, 5) should return false.
    return true; // Just a placeholder
}

// Function to perform binary search and find a 1 bit position
int find_one_bit_position(int range_start, int range_end) {
    int original_start = range_start; // Original bounds
    int original_end = range_end;

    // Perform binary search
    while (range_start < range_end) {
        int mid = (range_start + range_end) / 2;
        if (api_call(range_start, mid)) {
            range_end = mid; // Narrow the search to the left half
        } else {
            range_start = mid + 1; // Narrow the search to the right half
        }
    }

    // Check a few positions around the final narrowed-down index
    for (int index = range_start - 2; index <= range_start + 2; index++) {
        if (index >= original_start && index <= original_end && api_call(index, index)) {
            return index; // Found a position with a 1 bit
        }
    }

    return INF; // No 1 bit found in the range
}

int main() {
    int array_size = 10; // Example size of the bit array
    int current_index = 0; // Start index

    while (current_index < array_size) {
        int search_start = current_index;
        int search_end = array_size - 1;

        int found_position = find_one_bit_position(search_start, search_end);

        if (found_position < array_size) {
            positions_of_ones.push_back(found_position); // Found a 1 bit, store the position
        }

        current_index = found_position + 1; // Move to the next index after the found position
    }

    // Output the positions of 1 bits
    cout << "Positions of 1 bits: ";
    for (int position : positions_of_ones) {
        cout << position << " ";
    }
    cout << endl;

    return 0;
}
