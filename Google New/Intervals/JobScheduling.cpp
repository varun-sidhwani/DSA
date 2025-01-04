Given an array of meeting blocks for each person, each person has a range of days they are unavailable,
The following is a block structure:
It was given :
class block:
int personId;
int startDay;
int endDay;
Find all the days where everyone is available. Return 0 if there are no available slots

https://leetcode.com/discuss/interview-question/5748871/

https://leetcode.com/problems/count-days-without-meetings/description/


#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Block {
public:
    int personId;
    int startDay;
    int endDay;
    Block(int personId, int startDay, int endDay) 
        : personId(personId), startDay(startDay), endDay(endDay) {}
};

vector<int> findAllAvailableDays(int totalDays, vector<Block>& blocks, int totalPeople) {
    vector<int> unavailableDays(totalDays + 1, 0); // Track unavailability

    // Mark unavailable days
    for (auto& block : blocks) {
        unavailableDays[block.startDay] += 1;
        if (block.endDay + 1 <= totalDays) {
            unavailableDays[block.endDay + 1] -= 1;
        }
    }

    // Compute prefix sums to find days when everyone is unavailable
    for (int i = 1; i <= totalDays; i++) {
        unavailableDays[i] += unavailableDays[i - 1];
    }

    vector<int> availableDays;
    for (int i = 1; i <= totalDays; i++) {
        if (unavailableDays[i] == 0) { // Everyone is available
            availableDays.push_back(i);
        }
    }

    return availableDays.empty() ? vector<int>{0} : availableDays;
}
------------------



vector<int> findDaysWithAtLeastPAvailable(int totalDays, vector<Block>& blocks, int totalPeople, int P) {
    vector<int> unavailableDays(totalDays + 1, 0);

    // Mark unavailable days
    for (auto& block : blocks) {
        unavailableDays[block.startDay] += 1;
        if (block.endDay + 1 <= totalDays) {
            unavailableDays[block.endDay + 1] -= 1;
        }
    }

    // Compute prefix sums to find the number of unavailable people
    for (int i = 1; i <= totalDays; i++) {
        unavailableDays[i] += unavailableDays[i - 1];
    }

    vector<int> resultDays;
    for (int i = 1; i <= totalDays; i++) {
        int availablePeople = totalPeople - unavailableDays[i];
        if (availablePeople >= P) {
            resultDays.push_back(i);
        }
    }

    return resultDays.empty() ? vector<int>{0} : resultDays;
}
---------------------

vector<pair<int, int>> findPeriodsWithPAvailableForXDays(int totalDays, vector<Block>& blocks, int totalPeople, int P, int X) {
    vector<int> unavailableDays(totalDays + 1, 0);

    // Mark unavailable days
    for (auto& block : blocks) {
        unavailableDays[block.startDay] += 1;
        if (block.endDay + 1 <= totalDays) {
            unavailableDays[block.endDay + 1] -= 1;
        }
    }

    // Compute prefix sums to find the number of unavailable people
    for (int i = 1; i <= totalDays; i++) {
        unavailableDays[i] += unavailableDays[i - 1];
    }

    // Find periods with at least P people available for at least X consecutive days
    vector<pair<int, int>> periods;
    int start = -1, length = 0;

    for (int i = 1; i <= totalDays; i++) {
        int availablePeople = totalPeople - unavailableDays[i];
        if (availablePeople >= P) {
            if (start == -1) {
                start = i; // Start of a new period
            }
            length++;
        } else {
            if (length >= X) {
                periods.emplace_back(start, start + length - 1);
            }
            start = -1;
            length = 0;
        }
    }

    // Handle case where the last period extends to the end
    if (length >= X) {
        periods.emplace_back(start, start + length - 1);
    }

    return periods;
}
