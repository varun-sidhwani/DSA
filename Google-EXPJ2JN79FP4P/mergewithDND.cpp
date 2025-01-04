https://leetcode.com/discuss/interview-question/5848425/My-Google-SWE-Interview-Experience

#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int start, end;
    Interval(int s, int e) : start(s), end(e) {}
};

// Helper function to merge overlapping intervals
vector<Interval> mergeIntervals(vector<Interval> &intervals) {
    if (intervals.empty()) return {};

    // Sort by start time
    sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
        return a.start < b.start;
    });

    vector<Interval> merged;
    Interval current = intervals[0];

    for (int i = 1; i < (int)intervals.size(); i++) {
        // If intervals overlap or touch, merge
        if (intervals[i].start <= current.end) {
            current.end = max(current.end, intervals[i].end);
        } else {
            // No overlap, push current to merged list, move on
            merged.push_back(current);
            current = intervals[i];
        }
    }
    // Push the last interval
    merged.push_back(current);
    return merged;
}

// Apply DND constraints and split or remove intervals if needed
vector<Interval> applyDND(vector<Interval> &merged, Interval dnd) {
    vector<Interval> result;
    int dndStart = dnd.start;
    int dndEnd   = dnd.end;

    for (auto &interval : merged) {
        // If interval is completely outside DND
        if (interval.end <= dndStart || interval.start >= dndEnd) {
            // No change
            result.push_back(interval);
        }
        // If interval is fully within DND, skip it
        else if (interval.start >= dndStart && interval.end <= dndEnd) {
            // do nothing (interval is removed)
        }
        else {
            // Partial overlap scenarios
            // 1) Overlaps at the end of the interval
            if (interval.start < dndStart && interval.end > dndStart && interval.end <= dndEnd) {
                result.push_back(Interval(interval.start, dndStart));
            }
            // 2) Overlaps at the beginning of the interval
            else if (interval.start >= dndStart && interval.start < dndEnd && interval.end > dndEnd) {
                result.push_back(Interval(dndEnd, interval.end));
            }
            // 3) Interval covers the entire DND, split into two
            else if (interval.start < dndStart && interval.end > dndEnd) {
                result.push_back(Interval(interval.start, dndStart));
                result.push_back(Interval(dndEnd, interval.end));
            }
        }
    }
    return result;
}

int main() {
    // Example usage:
    // Meetings
    vector<Interval> meetings = {
        Interval(1, 3), Interval(2, 5),
        Interval(7, 9), Interval(8, 10)
    };
    // DND interval
    Interval dnd(4, 6);

    // Step 1: Merge intervals
    vector<Interval> merged = mergeIntervals(meetings);

    // Step 2: Apply DND rules
    vector<Interval> finalList = applyDND(merged, dnd);

    // Print results
    cout << "Final Intervals after merging and DND:\n";
    for (auto &i : finalList) {
        cout << "(" << i.start << ", " << i.end << ") ";
    }
    cout << endl;

    return 0;
}
z