// https://leetcode.com/discuss/interview-question/6179661/Google-L4-Phone-Screen


#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Function to calculate Euclidean distance between two routers
double calculateDistance(pair<int, int> router1, pair<int, int> router2) {
    int x1 = router1.first, y1 = router1.second;
    int x2 = router2.first, y2 = router2.second;
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Function to check if a signal can reach the destination
bool canReachDestination(
    const unordered_map<string, pair<int, int>>& routers, 
    const unordered_map<string, double>& ranges, 
    const string& source, 
    const string& destination
) {
    // Build adjacency list based on routers' ranges
    unordered_map<string, vector<string>> adjList;

    for (const auto& router1 : routers) {
        for (const auto& router2 : routers) {
            if (router1.first != router2.first) {
                double distance = calculateDistance(router1.second, router2.second);
                if (distance <= ranges.at(router1.first)) {
                    adjList[router1.first].push_back(router2.first);
                }
            }
        }
    }

    // BFS to check if the destination is reachable from the source
    unordered_set<string> visited;
    queue<string> q;
    
    visited.insert(source); // Mark source as visited before adding to queue
    q.push(source);

    while (!q.empty()) {
        string current = q.front();
        q.pop();
        
        if (current == destination) {
            return true;
        }

        for (const string& neighbor : adjList[current]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);  // Mark neighbor as visited when it's enqueued
                q.push(neighbor);
            }
        }
    }

    return false;
}

int main() {
    // Define router coordinates
    unordered_map<string, pair<int, int>> routers = {
        {"RouterA", {0, 0}},
        {"RouterB", {3, 4}},
        {"RouterC", {6, 8}},
        {"RouterD", {10, 10}}
    };

    // Define router communication ranges
    unordered_map<string, double> ranges = {
        {"RouterA", 5},
        {"RouterB", 6},
        {"RouterC", 4},
        {"RouterD", 7}
    };

    string source = "RouterA";
    string destination = "RouterD";

    bool result = canReachDestination(routers, ranges, source, destination);
    cout << (result ? "Yes" : "No") << endl;

    return 0;
}
