Onsite 2: Given 12 tiles, each with a color and a number. 
Find if 4 winning hands exist. 1 winning hand consists of 3 tiles, 
and is decided by either all tiles are same (both colour and number) or 
(color is same but number are consecutive)


#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

// Helper function to check if a group of 3 tiles forms a winning hand
bool isWinningHand(const vector<pair<string, int>>& group) {
    if (group.size() != 3) return false;

    // Check if all tiles are the same (color and number)
    if (group[0] == group[1] && group[1] == group[2]) {
        return true;
    }

    // Check if all tiles have the same color and consecutive numbers
    if (group[0].first == group[1].first && group[1].first == group[2].first) {
        vector<int> numbers = {group[0].second, group[1].second, group[2].second};
        sort(numbers.begin(), numbers.end());
        if (numbers[1] == numbers[0] + 1 && numbers[2] == numbers[1] + 1) {
            return true;
        }
    }

    return false;
}

// Backtracking function to find 4 winning hands
bool findWinningHands(vector<pair<string, int>>& tiles, vector<vector<pair<string, int>>>& groups) {
    // Pruning: If we already have 4 groups, validate and stop
    if (groups.size() == 4) {
        for (const auto& group : groups) {
            if (!isWinningHand(group)) return false;
        }
        return true;
    }

    // Pruning: If remaining tiles cannot form valid groups, stop
    if ((tiles.size() % 3) != 0) return false;

    // Try forming a group of 3 tiles
    for (int i = 0; i < tiles.size(); ++i) {
        for (int j = i + 1; j < tiles.size(); ++j) {
            for (int k = j + 1; k < tiles.size(); ++k) {
                // Form a group
                vector<pair<string, int>> group = {tiles[i], tiles[j], tiles[k]};
                if (!isWinningHand(group)) continue; // Pruning: Skip invalid groups

                // Remove these tiles from the pool
                vector<pair<string, int>> remaining;
                for (int x = 0; x < tiles.size(); ++x) {
                    if (x != i && x != j && x != k) {
                        remaining.push_back(tiles[x]);
                    }
                }

                // Add the group and recurse
                groups.push_back(group);
                if (findWinningHands(remaining, groups)) {
                    return true;
                }
                groups.pop_back(); // Backtrack
            }
        }
    }

    return false;
}

int main() {
    // Example tiles: {color, number}
    vector<pair<string, int>> tiles = {
        {"red", 1}, {"red", 2}, {"red", 3},
        {"blue", 4}, {"blue", 4}, {"blue", 4},
        {"green", 5}, {"green", 6}, {"green", 7},
        {"yellow", 8}, {"yellow", 8}, {"yellow", 8}
    };

    vector<vector<pair<string, int>>> groups;
    if (findWinningHands(tiles, groups)) {
        cout << "4 winning hands exist!" << endl;
    } else {
        cout << "No valid grouping found." << endl;
    }

    return 0;
}
