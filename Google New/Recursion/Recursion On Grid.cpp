https://leetcode.com/discuss/interview-question/6219667/Google-Senior-engineer


#include <iostream>
using namespace std;

int oqcsValue(int x, int y, int size) {
    if (size == 1) {
        // Base case: single point
        return 0;
    }

    // Size of a quadrant
    int halfSize = size / 2;
    int quadrantSize = halfSize * halfSize;

    if (x < halfSize && y < halfSize) {
        // Lower-left quadrant
        return oqcsValue(x, y, halfSize);
    } else if (x < halfSize && y >= halfSize) {
        // Upper-left quadrant
        return quadrantSize + oqcsValue(x, y - halfSize, halfSize);
    } else if (x >= halfSize && y >= halfSize) {
        // Upper-right quadrant
        return 2 * quadrantSize + oqcsValue(x - halfSize, y - halfSize, halfSize);
    } else {
        // Lower-right quadrant
        return 3 * quadrantSize + oqcsValue(x - halfSize, y, halfSize);
    }
}

int main() {
    int size = 16; // Example size: 2^4
    int x = 1, y = 1; // Example coordinates

    cout << "The OQCS value of point (" << x << ", " << y << ") is: "
         << oqcsValue(x, y, size) << endl;

    return 0;
}
