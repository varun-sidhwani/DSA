BFS - 

class Solution {
public:
    int minimumSemesters(int N, vector<vector<int>>& relations) {
        // Build the graph and compute in-degrees
        vector<vector<int>> graph(N + 1);
        vector<int> inDegree(N + 1, 0);
        for (const auto& relation : relations) {
            graph[relation[0]].push_back(relation[1]);
            inDegree[relation[1]]++;
        }

        // Initialize the queue with nodes having in-degree of 0
        vector<int> queue;
        for (int node = 1; node <= N; ++node) {
            if (inDegree[node] == 0) {
                queue.push_back(node);
            }
        }

        int semesters = 0, studiedCount = 0;

        // BFS to process courses semester by semester
        while (!queue.empty()) {
            semesters++;
            vector<int> nextQueue;
            for (int node : queue) {
                studiedCount++;
                for (int neighbor : graph[node]) {
                    if (--inDegree[neighbor] == 0) {
                        nextQueue.push_back(neighbor);
                    }
                }
            }
            queue = move(nextQueue);
        }

        // Check if all courses have been studied
        return studiedCount == N ? semesters : -1;
    }
};

DFS - Find the longest path - this will be the limiting factor and hence the minimum time to complete all courses.
class Solution {
public:
    int minimumSemesters(int N, vector<vector<int>>& relations) {
        // Build the adjacency list for the graph
        vector<vector<int>> graph(N + 1);
        for (const auto& relation : relations) {
            graph[relation[0]].push_back(relation[1]);
        }

        // Visited states: 
        // 0 = unvisited, -1 = visiting (detect cycle), >0 = longest path to this node
        vector<int> visited(N + 1, 0);
        int maxSemesters = 1;

        // Perform DFS for each node
        for (int node = 1; node <= N; ++node) {
            int pathLength = dfs(node, graph, visited);
            if (pathLength == -1) { // Cycle detected
                return -1;
            }
            maxSemesters = max(maxSemesters, pathLength);
        }

        return maxSemesters;
    }

private:
    int dfs(int node, const vector<vector<int>>& graph, vector<int>& visited) {
        if (visited[node] != 0) {
            return visited[node]; // Return cached result or detect a cycle
        }

        // Mark node as being visited (cycle detection)
        visited[node] = -1;

        int maxLength = 1; // Minimum path length is 1 (itself)
        for (int neighbor : graph[node]) {
            int pathLength = dfs(neighbor, graph, visited);
            if (pathLength == -1) {
                return -1; // Cycle detected
            }
            maxLength = max(maxLength, pathLength + 1);
        }

        // Mark node as fully processed and cache result
        visited[node] = maxLength;
        return maxLength;
    }
};
