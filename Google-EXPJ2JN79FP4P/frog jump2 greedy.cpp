// Claim 1: It is optimal that we make use of all rocks: There is never a benefit of not including a rock in Path 1 or Path 2, it is always positive or neutral.
// Claim 2: It is never optimal to choose two consecutive rocks: If we choose rock_i, and rock_i+1, then rock_i+2 will have to do (rock_i+2)-(rock_i) work to return. Because the array is strictly increasing, it holds that (rock_i+2)-(rock_i) > (rock_i+1-rock_i)
// Therefore one path must lie on each even index and the other path must lie on each odd index. We iterate through them and find the maximum distance.


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxFrogJump(vector<int>& rocks) {
    int maxOdd = 0; // Maximum jump for the odd-indexed path
    int maxEven = 0; // Maximum jump for the even-indexed path

    // Iterate through the rocks in a single pass
    for (int i = 1; i < rocks.size(); ++i) {
        if (i % 2 == 1) {
            // Odd index jump
            maxOdd = max(maxOdd, rocks[i] - rocks[i - 1]);
        } else {
            // Even index jump
            maxEven = max(maxEven, rocks[i] - rocks[i - 1]);
        }
    }

    // Return the maximum of the two paths
    return max(maxOdd, maxEven);
}

int main() {
    vector<int> rocks = {1, 2, 5, 7, 10};
    cout << "Maximum Frog Jump: " << maxFrogJump(rocks) << endl;
    return 0;
}
