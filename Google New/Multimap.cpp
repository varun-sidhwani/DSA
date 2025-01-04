https://leetcode.com/discuss/interview-question/5869928/Google-Screening-Round-L4

#include <iostream>
#include <map>
#include <unordered_map>
#include <chrono>
using namespace std;

class RestaurantWaitlist {
    multimap<pair<int, long long>, int> waitingQueue; // { {groupSize, arrivalTime}, groupId }
    unordered_map<int, multimap<pair<int, long long>, int>::iterator> partyMap; // { groupId, iterator in waitingQueue }

    // Get current time in milliseconds
    long long currentTimeMillis() {
        return chrono::duration_cast<chrono::milliseconds>(
                   chrono::system_clock::now().time_since_epoch())
            .count();
    }

public:
    // Add a group to the waitlist
    void join(int groupId, int numPeople) {
        if (partyMap.find(groupId) != partyMap.end()) {
            throw invalid_argument("Group ID already in the waitlist");
        }

        long long arrivalTime = currentTimeMillis();
        auto it = waitingQueue.insert({{numPeople, arrivalTime}, groupId}); // Insert with arrivalTime
        partyMap[groupId] = it; // Store iterator in partyMap
    }

    // Remove a group from the waitlist
    void leave(int groupId) {
        if (partyMap.find(groupId) == partyMap.end()) {
            throw invalid_argument("Group ID not found in the waitlist");
        }

        auto it = partyMap[groupId];
        waitingQueue.erase(it); // Remove from multimap
        partyMap.erase(groupId); // Remove from partyMap
    }

    // Serve the first group that fits the table size
    int serve(int tableSize) {
        auto it = waitingQueue.upper_bound({tableSize, LLONG_MAX}); // Find largest group ≤ tableSize

        if (it == waitingQueue.begin()) {
            return -1; // No group fits the table
        }

        --it; // Get the largest group that fits
        int groupId = it->second;

        waitingQueue.erase(it); // Remove from multimap
        partyMap.erase(groupId); // Remove from partyMap

        return groupId;
    }

    // Debug function to print the current waitlist
    void printWaitlist() {
        cout << "Current Waitlist:" << endl;
        for (const auto& entry : waitingQueue) {
            cout << "Group Size: " << entry.first.first
                 << ", Arrival Time: " << entry.first.second
                 << ", Group ID: " << entry.second << endl;
        }
        cout << endl;
    }
};

int main() {
    RestaurantWaitlist waitlist;

    // Test the implementation
    waitlist.join(1, 4); // Group 1, size 4
    waitlist.join(2, 6); // Group 2, size 6
    waitlist.join(3, 4); // Group 3, size 4 (later arrival time than Group 1)
    waitlist.join(4, 2); // Group 4, size 2

    waitlist.printWaitlist();

    cout << "Serving Table of Size 5: Group ID " << waitlist.serve(5) << endl;
    waitlist.printWaitlist();

    waitlist.leave(3); // Group 3 leaves
    waitlist.printWaitlist();

    cout << "Serving Table of Size 6: Group ID " << waitlist.serve(6) << endl;
    waitlist.printWaitlist();

    return 0;
}
