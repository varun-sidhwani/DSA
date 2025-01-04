https://leetcode.com/discuss/interview-question/5826383/Google-Phone-Screen-or-L4-or-US

string findPassword(vector<string>& tuples) {
    unordered_map<char, unordered_set<char>> graph; // Adjacency list
    unordered_map<char, int> inDegree;             // In-degree of each node
    unordered_set<char> allChars;                  // Set of all unique characters

    // Step 1: Build the graph and calculate in-degrees
    for (string& tuple : tuples) {
        for (char c : tuple) {
            allChars.insert(c);
            if (inDegree.find(c) == inDegree.end()) {
                inDegree[c] = 0;
            }
        }
        for (int i = 0; i < tuple.size() - 1; i++) {
            char from = tuple[i];
            char to = tuple[i + 1];
            if (graph[from].find(to) == graph[from].end()) {
                graph[from].insert(to);
                inDegree[to]++;
            }
        }
    }

    // Step 2: Perform topological sorting using Kahn's algorithm
    queue<char> zeroInDegree; // Nodes with 0 in-degree
    for (char c : allChars) {
        if (inDegree[c] == 0) {
            zeroInDegree.push(c);
        }
    }

    string password;
    while (!zeroInDegree.empty()) {
        char current = zeroInDegree.front();
        zeroInDegree.pop();
        password += current;

        for (char neighbor : graph[current]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                zeroInDegree.push(neighbor);
            }
        }
    }

    // Step 3: Check for a valid topological sort (all characters used)
    if (password.size() != allChars.size()) {
        return ""; // No valid password if not all characters are used
    }

    return password;
}

int main() {
    vector<string> tuples = {"bca", "bcd", "cad"};
    string password = findPassword(tuples);

    if (!password.empty()) {
        cout << "The password is: " << password << endl;
    } else {
        cout << "No valid password could be generated." << endl;
    }

    return 0;
}



https://leetcode.com/discuss/interview-question/5813714/Google-Interview-Question

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

// Function to build the graph from the input steps
void buildGraph(const vector<string>& steps, unordered_map<string, unordered_set<string>>& graph, unordered_map<string, int>& inDegree) {
    for (int i = 0; i < steps.size() - 1; i++) {
        string from = steps[i];
        string to = steps[i + 1];
        // Add edge and update in-degree
        if (graph[from].find(to) == graph[from].end()) {
            graph[from].insert(to);
            inDegree[to]++;
        }
        if (inDegree.find(from) == inDegree.end()) {
            inDegree[from] = 0; // Ensure the node exists in in-degree map
        }
    }
    // Ensure the last step exists in the in-degree map
    if (inDegree.find(steps.back()) == inDegree.end()) {
        inDegree[steps.back()] = 0;
    }
}

// Function to perform topological sort
vector<string> topologicalSort(unordered_map<string, unordered_set<string>>& graph, unordered_map<string, int>& inDegree) {
    queue<string> zeroInDegree; // Nodes with in-degree 0
    vector<string> sortedOrder;

    // Find all nodes with in-degree 0
    for (auto& entry : inDegree) {
        if (entry.second == 0) {
            zeroInDegree.push(entry.first);
        }
    }

    // Process nodes with in-degree 0
    while (!zeroInDegree.empty()) {
        string current = zeroInDegree.front();
        zeroInDegree.pop();
        sortedOrder.push_back(current);

        for (const string& neighbor : graph[current]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                zeroInDegree.push(neighbor);
            }
        }
    }

    return sortedOrder;
}

int main() {
    // Input test sequences
    vector<vector<string>> tests = {
        {"A", "B", "C"},
        {"X", "B", "Z"}
    };

    // Step 1: Build the graph
    unordered_map<string, unordered_set<string>> graph; // Adjacency list
    unordered_map<string, int> inDegree;               // In-degree map

    for (const auto& steps : tests) {
        buildGraph(steps, graph, inDegree);
    }

    // Step 2: Perform topological sorting
    vector<string> optimizedSteps = topologicalSort(graph, inDegree);

    // Step 3: Output the result
    cout << "Optimized steps: ";
    for (const string& step : optimizedSteps) {
        cout << step << " ";
    }
    cout << endl;

    return 0;
}
