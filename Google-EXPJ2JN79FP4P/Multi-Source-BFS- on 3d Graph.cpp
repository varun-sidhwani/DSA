// You are given a 3D lattice graph where:

// Torch nodes (16) transmit power to adjacent wire nodes (0).
// Power decreases by 1 with each step and stops when it reaches 0 or another torch node.
// If multiple power sources reach a node, the node takes the highest power available.
// Goal
// Simulate power propagation from all torch nodes and return the final graph.


#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

// Define the directions for moving in the 3D lattice
const int dx[6] = {1, -1, 0, 0, 0, 0};
const int dy[6] = {0, 0, 1, -1, 0, 0};
const int dz[6] = {0, 0, 0, 0, 1, -1};

// BFS function to propagate power
void propagatePower(vector<vector<vector<int>>>& graph) {
    int xSize = graph.size();
    int ySize = graph[0].size();
    int zSize = graph[0][0].size();

    queue<tuple<int, int, int, int>> q; // Queue to store (x, y, z, power)

    // Push all torch nodes into the queue
    for (int x = 0; x < xSize; ++x) {
        for (int y = 0; y < ySize; ++y) {
            for (int z = 0; z < zSize; ++z) {
                if (graph[x][y][z] == 16) {
                    q.push({x, y, z, 16});
                }
            }
        }
    }

    // BFS propagation
    while (!q.empty()) {
        auto [x, y, z, power] = q.front();
        q.pop();

        // Check all 6 possible directions
        for (int i = 0; i < 6; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];

            // Check bounds
            if (nx >= 0 && ny >= 0 && nz >= 0 && nx < xSize && ny < ySize && nz < zSize) {
                // Check if we can propagate power
                if (graph[nx][ny][nz] < power - 1) {
                    graph[nx][ny][nz] = power - 1; // Update the node with the new power value
                    q.push({nx, ny, nz, power - 1}); // Add the updated node to the queue
                }
            }
        }
    }
}

int main() {
    // Input the 3D graph dimensions and initial values
    int xSize, ySize, zSize;
    cout << "Enter dimensions (x, y, z): ";
    cin >> xSize >> ySize >> zSize;

    vector<vector<vector<int>>> graph(xSize, vector<vector<int>>(ySize, vector<int>(zSize)));

    cout << "Enter the graph values (16 for torch nodes, 0 for wire nodes):\n";
    for (int x = 0; x < xSize; ++x) {
        for (int y = 0; y < ySize; ++y) {
            for (int z = 0; z < zSize; ++z) {
                cin >> graph[x][y][z];
            }
        }
    }

    // Propagate power
    propagatePower(graph);

    // Output the final graph
    cout << "Final graph after power propagation:\n";
    for (int x = 0; x < xSize; ++x) {
        for (int y = 0; y < ySize; ++y) {
            for (int z = 0; z < zSize; ++z) {
                cout << graph[x][y][z] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    return 0;
}



/* 



*/