https://leetcode.com/discuss/interview-question/5963260/Google-India-Interview-Experience-or-L4-or-phone-screen-or-onsite-or-reject
Round 2

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n;

    vector<pair<int, int>> polygon(n);
    for (int i = 0; i < n; ++i) {
        cin >> polygon[i].first >> polygon[i].second;
    }

    cin >> m;
    vector<pair<pair<int, int>, pair<int, int>>> ropes(m);
    for (int i = 0; i < m; ++i) {
        cin >> ropes[i].first.first >> ropes[i].first.second;
        cin >> ropes[i].second.first >> ropes[i].second.second;
    }

    vector<tuple<int, int, int, int, int>> events; // Events as (x, type, y1, y2, index)

    // Add polygon edges as events
    for (int i = 0; i < n; ++i) {
        int x1 = polygon[i].first, y1 = polygon[i].second;
        int x2 = polygon[(i + 1) % n].first, y2 = polygon[(i + 1) % n].second;

        if (x1 > x2) swap(x1, x2), swap(y1, y2);
        events.emplace_back(x1, 1, min(y1, y2), max(y1, y2), -1);  // Start of edge
        events.emplace_back(x2, -1, min(y1, y2), max(y1, y2), -1); // End of edge
    }

    // Add ropes as query events
    for (int i = 0; i < m; ++i) {
        int x1 = ropes[i].first.first, y1 = ropes[i].first.second;
        int x2 = ropes[i].second.first, y2 = ropes[i].second.second;

        if (x1 > x2) swap(x1, x2), swap(y1, y2);
        events.emplace_back(x1, 0, min(y1, y2), max(y1, y2), i); // Rope query
    }

    // Sort events by x-coordinate
    sort(events.begin(), events.end());

    set<pair<int, int>> activeSegments; // Set to track active y-ranges
    vector<double> results(m, 0);

    // Sweep line processing
    for (const auto& e : events) {
        int x = get<0>(e);
        int type = get<1>(e);
        int y1 = get<2>(e);
        int y2 = get<3>(e);
        int index = get<4>(e);

        if (type == 1) {
            // Add polygon edge
            activeSegments.insert({y1, y2});
        } else if (type == -1) {
            // Remove polygon edge
            activeSegments.erase({y1, y2});
        } else {
            // Query rope
            for (const auto& seg : activeSegments) {
                // Check if there is overlap between the rope's y-range and the active segment
                int overlapStart = max(seg.first, y1);
                int overlapEnd = min(seg.second, y2);
                if (overlapStart < overlapEnd) {
                    results[index] += (overlapEnd - overlapStart);
                }
            }
        }
    }

    // Output results
    for (const auto& res : results) {
        cout << res << endl;
    }

    return 0;
}
