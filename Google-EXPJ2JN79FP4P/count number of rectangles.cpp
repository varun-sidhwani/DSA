// I am given a list of points on x,y plane. We have to derive the maximum number of rectangles using those points. Rectangles may not neccessarily be inclined to x or y axis.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

struct Point {
    int x, y;
};

// Hash function for pair of integers
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

int countRectangles(vector<Point>& points) {
    int n = points.size();
    if (n < 4) return 0; // Not enough points to form a rectangle

    unordered_map<pair<pair<int, int>, int>, vector<pair<int, int>>, hash_pair> diagonals;

    // Iterate over all pairs of points
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Calculate midpoint and squared diagonal length
            int midX = points[i].x + points[j].x;
            int midY = points[i].y + points[j].y;
            int diagLength = pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2);

            // Group pairs by midpoint and diagonal length
            diagonals[{{midX, midY}, diagLength}].emplace_back(i, j);
        }
    }

    // Count rectangles
    int rectangleCount = 0;
    for (auto& [key, pairs] : diagonals) {
        int k = pairs.size();
        rectangleCount += (k * (k - 1)) / 2; // Choose 2 pairs out of k
    }

    return rectangleCount;
}

int main() {
    vector<Point> points = {{0, 0}, {2, 0}, {0, 2}, {2, 2}, {1, 1}};
    cout << "Number of rectangles: " << countRectangles(points) << endl;
    return 0;
}
