
https://leetcode.com/discuss/interview-question/5004476/Google-L5-Round-1

#include <iostream>
#include <queue>
#include <vector>

bool isValidTournament(std::vector<int>& nums) {
    int len = nums.size();
    if (len % 2 != 0) {
        return false; // Tournament must have even number of players
    }

    std::queue<int> q;
    for (int num : nums) {
        q.push(num); // Add players to the queue
    }

    while (q.size() > 1) {
        int size = q.size();
        for (int i = 0; i < size; i += 2) {
            int player1 = q.front(); q.pop(); // Get first player
            int player2 = q.front(); q.pop(); // Get second player
            
            // Check if the two players form a valid pair
            if (player1 + player2 != size + 1) {
                return false;
            }

            // Add the winner (minimum rank) to the next round
            q.push(std::min(player1, player2));
        }
    }

    return true;
}

int main() {
    std::vector<int> nums1 = {1, 8, 6, 2, 7, 3, 4, 5};
    std::vector<int> nums2 = {1, 2, 3, 4};

    std::cout << "Is nums1 valid? " << (isValidTournament(nums1) ? "Yes" : "No") << std::endl;
    std::cout << "Is nums2 valid? " << (isValidTournament(nums2) ? "Yes" : "No") << std::endl;

    return 0;
}
