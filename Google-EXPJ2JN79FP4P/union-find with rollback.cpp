https://leetcode.com/discuss/interview-question/4845526/Google-Interview-Question

https://chatgpt.com/share/676e5274-d968-8003-942a-fa44d63da244


#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class DSU {
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            // Save the state before performing the union
            history.push({rootX, parent[rootX], rootY, parent[rootY], rank[rootX], rank[rootY]});

            // Union by rank
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    void rollback() {
        if (history.empty()) return;
        
        auto lastState = history.top();
        history.pop();
        
        // Rollback to the previous state
        int rootX = lastState[0];
        int parentX = lastState[1];
        int rootY = lastState[2];
        int parentY = lastState[3];
        int rankX = lastState[4];
        int rankY = lastState[5];
        
        parent[rootX] = parentX;
        parent[rootY] = parentY;
        rank[rootX] = rankX;
        rank[rootY] = rankY;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    bool allConnected(int n) {
        int root = find(0);
        for (int i = 1; i < n; ++i) {
            if (find(i) != root) {
                return false;
            }
        }
        return true;
    }

private:
    vector<int> parent, rank;
    stack<vector<int>> history;  // Stack to store the history of union operations
};

int earliestFullConnection(vector<vector<int>>& logs, int n) {
    DSU dsu(n);
    
    for (auto& log : logs) {
        int timestamp = log[0];
        int x = log[1];
        int y = log[2];

        dsu.unionSets(x, y);

        if (dsu.allConnected(n)) {
            return timestamp;
        }
    }

    return -1;  // If not all are connected
}

int main() {
    int n = 4;  // Number of people
    vector<vector<int>> logs = {{0, 0, 1}, {1, 1, 2}, {2, 2, 3}, {3, 0, 3}};
    
    int result = earliestFullConnection(logs, n);
    cout << "Earliest time when everyone is acquainted: " << result << endl;
    
    return 0;
}
