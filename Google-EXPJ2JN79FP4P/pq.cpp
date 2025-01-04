https://leetcode.com/discuss/interview-question/4949834/Google-or-SDE2-or-Phone-Screen


/*

you are given an array of houses in a neighboorhood in a city.
you have to rearrange houses in such a way that in a single neighbourhood the houses are sorted by number in ascending order and no 2 houses with same number are in same neighbourhood.
you can only rearrange house based on the capacity of each neighbourhood . If neighbourhood "1" in input has 2 houses then at output also it can only have 2 houses.


For example-
{
{1,2},
{4,4,7,8},
{4,9,9,9}
}


becomes
{
{4,9},
{1,2,4,9},
{4,7,8,9}
}


*/


#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

vector<vector<int>> rearrangeNeighbourhood(vector<vector<int>> nums) {
    unordered_map<int, int> freq;
    vector<pair<int, int>> capacity; // {remaining_capacity, index}
    int i = 0;

    // Count frequencies and store capacities
    for (auto& num : nums) {
        capacity.push_back({(int)num.size(), i++});
        for (auto& n : num) {
            freq[n]++;
        }
    }

    // Priority queue to process numbers by frequency
    priority_queue<pair<int, int>> pq; // {frequency, number}
    for (auto& f : freq) {
        pq.push({f.second, f.first});
    }

    // Initialize result with empty sets
    vector<set<int>> subResult(nums.size());

    // Sort capacities by remaining capacity
    sort(capacity.begin(), capacity.end());

    // Distribute numbers across neighborhoods
    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();

        int count = curr.first;
        int n = curr.second;

        for (auto& cap : capacity) {
            if (cap.first > 0 && count > 0) {
                subResult[cap.second].insert(n);
                cap.first -= 1; // Reduce capacity
                count -= 1;     // Reduce frequency of the number
            }
            if (count == 0) break;
        }
    }

    // Convert sets to vectors for final result
    vector<vector<int>> res;
    for (auto& sub : subResult) {
        res.push_back(vector<int>(sub.begin(), sub.end()));
    }

    return res;
}
