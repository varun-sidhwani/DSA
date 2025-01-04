https://leetcode.com/discuss/interview-question/1471821/Google-screening-round-Job-scheduling

/*

Here’s how it works in your code:

Event Marking:
You iterate over each job in the jobs vector and for each job, you create two events:

At the job's start time it[0], you add the job's capacity it[2] (this indicates the capacity requirement increases).
At the job's end time it[1], you subtract the job's capacity it[2] (this indicates the capacity requirement decreases).
These two operations essentially mark the "events" at which the capacity usage changes.

Sweeping through Events:
You then traverse the events in a sorted order of times. This is done by iterating over the map<int, int> mp where each key is a time point, and the value is the change in capacity at that time.

As you "sweep" through the timeline, you maintain a running total (cnt) of the current capacity usage. If at any point, cnt exceeds the capacity, it means scheduling is not possible, and you return false.



*/

#include <vector>
#include <map>
using namespace std;

bool isJobSchedulingPossible(vector<vector<int>>& jobs, int capacity) {
    // Map to store the events: start time -> increase in capacity, end time -> decrease in capacity
    map<int, int> events;

    // Populate the events map with start and end times of jobs
    for (const auto& job : jobs) {
        int start = job[0];  // Start time
        int end = job[1];    // End time
        int load = job[2];   // Capacity required by the job

        // Increase capacity at start time, decrease at end time
        events[start] += load;
        events[end] -= load;
    }

    // Track the current capacity usage
    int currentCapacity = 0;

    // Sweep through the events sorted by time
    for (const auto& event : events) {
        currentCapacity += event.second;

        // If the current capacity exceeds the given capacity, return false
        if (currentCapacity > capacity) {
            return false;
        }
    }

    // If no point exceeds the capacity, return true
    return true;
}
