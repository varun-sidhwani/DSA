https://leetcode.com/problems/rectangle-area-ii/description/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// A constant for modulo
const int MOD = 1e9 + 7;

// Event structure
struct Event {
    int x, y1, y2, type; // x-coordinate, y-range, and type (+1 for start, -1 for end)
    Event(int x, int y1, int y2, int type) : x(x), y1(y1), y2(y2), type(type) {}
};

// Calculate the union of intervals
int calculateUnion(map<int, int>& activeY) {
    int total = 0, prevY = -1, count = 0;

    for (const auto& [y, cnt] : activeY) {
        if (count > 0) {
            total += y - prevY;
        }
        count += cnt;
        prevY = y;
    }

    return total;
}

int rectangleArea(vector<vector<int>>& rectangles) {
    vector<Event> events;

    // Create events
    for (const auto& rect : rectangles) {
        int x1 = rect[0], y1 = rect[1], x2 = rect[2], y2 = rect[3];
        events.emplace_back(x1, y1, y2, 1);  // Start event
        events.emplace_back(x2, y1, y2, -1); // End event
    }

    // Sort events by x; if x is the same, end (-1) comes before start (+1)
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.x < b.x || (a.x == b.x && a.type < b.type);
    });

    map<int, int> activeY; // Active y-intervals
    int prevX = events[0].x, result = 0;

    // Line sweep
    for (const auto& event : events) {
        // Calculate the vertical area at the previous x
        int verticalLength = calculateUnion(activeY);
        result = (result + (long long)verticalLength * (event.x - prevX)) % MOD;

        // Update active y-intervals
        if (event.type == 1) {
            activeY[event.y1]++;
            activeY[event.y2]--;
        } else {
            activeY[event.y1]--;
            activeY[event.y2]++;
        }

        // Remove zero-count intervals
        if (activeY[event.y1] == 0) activeY.erase(event.y1);
        if (activeY[event.y2] == 0) activeY.erase(event.y2);

        prevX = event.x;
    }

    return result;
}
