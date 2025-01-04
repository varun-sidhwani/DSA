https://leetcode.com/problems/my-calendar-i/


class MyCalendar {
public:
    set<pair<int, int>> calendar;
    MyCalendar() {
    }
    
    bool book(int start, int end) {
        auto nextEvent = calendar.lower_bound({start, end});
        
        // Check if the current event overlaps with the next event
        if (nextEvent != calendar.end() && nextEvent->first < end) {
            return false;
        }
        
        // Check if the current event overlaps with the previous event
        if (nextEvent != calendar.begin() && std::prev(nextEvent)->second > start) {
            return false;
        }
        
        // No overlaps, insert the event
        calendar.insert({start, end});
        return true;
    }
};


