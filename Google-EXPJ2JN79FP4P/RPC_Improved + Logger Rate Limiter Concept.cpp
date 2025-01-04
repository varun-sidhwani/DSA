https://leetcode.com/discuss/interview-question/924141/google-phone-screen-new-grad
// this is using set and queue
// if you have time check how to use it with doubly linked list

Normal input based - 

#include <queue>
#include <unordered_set>
#include <vector>
#include <utility>
using namespace std;

// Event structure
struct Event {
    int id;
    int timestamp;
    string type; // "start" or "end"
};

pair<int, int> earliestTimeout(vector<Event> events, int timeout) {
    queue<pair<int, int>> q; // Queue of {id, expiry_time}
    unordered_set<int> activeRequests; // Set of active request IDs

    for (const auto& event : events) {
        // Remove expired events from the queue
        while (!q.empty() && event.timestamp > q.front().second) {
            auto& curr = q.front();
            q.pop();

            if (activeRequests.find(curr.first) != activeRequests.end()) {
                // Found a timeout
                return {curr.first, curr.second};
            }
        }

        if (event.type == "start") {
            // Add a new request to the queue and active set
            q.push({event.id, event.timestamp + timeout});
            activeRequests.insert(event.id);
        } else if (event.type == "end") {
            // Remove the request from the active set
            activeRequests.erase(event.id);
        }
    }

    // If no timeouts found
    return {-1, -1};
}


Stream based input - 

#include <queue>
#include <unordered_set>
#include <utility>
using namespace std;

// Event structure
struct Event {
    int id;
    int timestamp;
    string type; // "start" or "end"
};

// Function to process the stream and find the earliest timeout
pair<int, int> earliestTimeoutFromStream(int timeout, function<bool(Event&)> getNextEvent) {
    queue<pair<int, int>> q; // Queue of {id, expiry_time}
    unordered_set<int> activeRequests; // Set of active request IDs

    Event event; // Current event being processed

    while (getNextEvent(event)) {
        // Process timeout for expired events in the queue
        while (!q.empty() && event.timestamp > q.front().second) {
            auto& curr = q.front();
            q.pop();

            if (activeRequests.find(curr.first) != activeRequests.end()) {
                // Found a timeout
                return {curr.first, curr.second};
            }
        }

        if (event.type == "end") {
            // Remove the request from the active set
            activeRequests.erase(event.id);
        } else if (event.type == "start") {
            // Add new request to queue and active set
            q.push({event.id, event.timestamp + timeout});
            activeRequests.insert(event.id);
        }
    }

    // If no timeouts found
    return {-1, -1};
}


Time Complexity
Let n be the total number of events in the stream:

Processing Events:
Each event is processed once, so this contributes O(n).
Queue Operations:
Each event is added to and removed from the queue exactly once. These operations are O(1) each, so this also contributes O(n).
Set Operations:
Each insertion and deletion from the unordered_set is O(1) on average. 
With n events, this contributes O(n).