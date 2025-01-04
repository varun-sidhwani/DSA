

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Function to analyze RPC logs
vector<pair<string, int>> analyzeRPCLogs(const vector<tuple<int, string, string>>& logs, int threshold) {
    unordered_map<string, int> rpcStartTimes; // Map to store start times for RPCs
    vector<pair<string, int>> longRpcs;       // Store RPCs exceeding threshold

    for (const auto& log : logs) {
        int time;
        string rpcId, status;
        tie(time, rpcId, status) = log;

        if (status == "START") {
            rpcStartTimes[rpcId] = time;
        } else if (status == "END") {
            if (rpcStartTimes.find(rpcId) != rpcStartTimes.end()) {
                int startTime = rpcStartTimes[rpcId];
                int duration = time - startTime;
                if (duration > threshold) {
                    longRpcs.emplace_back(rpcId, duration);
                }
                rpcStartTimes.erase(rpcId); // Remove the completed RPC
            } else {
                cerr << "Warning: END log found for unknown RPC_ID " << rpcId << endl;
            }
        }
    }

    // Check for timeouts (RPCs with START but no END)
    for (const auto& entry : rpcStartTimes) {
        cerr << "Timeout: RPC_ID " << entry.first << " started at time " << entry.second << " but has no END entry" << endl;
    }

    return longRpcs;
}

int main() {
    // Example logs: {time, RPC_ID, status}
    vector<tuple<int, string, string>> logs = {
        {0, "RPC_1", "START"},
        {60, "RPC_1", "END"},
        {120, "RPC_2", "START"},
        {300, "RPC_2", "END"},
        {360, "RPC_3", "START"}
    };

    int threshold = 120; // Threshold in seconds

    vector<pair<string, int>> longRpcs = analyzeRPCLogs(logs, threshold);

    // Output long-running RPCs
    cout << "Long-running RPCs:" << endl;
    for (const auto& rpc : longRpcs) {
        cout << "RPC_ID: " << rpc.first << ", Duration: " << rpc.second << " seconds" << endl;
    }

    return 0;
}
