https://leetcode.com/discuss/interview-question/5676823/Google-L4-or-SWE3-Phone-Screen


struct Topping {
    int startX, endX;
    int startY, endY; // Not used for a vertical cut check
};

bool canMakeVerticalCut(const vector<Topping>& toppings) {
    // Need at least 2 toppings to have one on each side
    if (toppings.size() < 2) return false;
    
    // Extract just the x-intervals
    vector<pair<int,int>> intervals;
    intervals.reserve(toppings.size());
    for (auto &t : toppings) {
        intervals.push_back({t.startX, t.endX});
    }
    
    // Sort intervals by startX
    sort(intervals.begin(), intervals.end(), 
         [](auto &a, auto &b){
             return a.first < b.first;
         }
    );
    
    // Sweep from left to right, tracking maxEndX
    int maxEndX = intervals[0].second;
    
    // Check for a gap between consecutive toppings
    for (int i = 1; i < (int)intervals.size(); i++) {
        // If there's a gap between the previous maxEndX and the current startX
        if (intervals[i].first > maxEndX) {
            // We have a gap, and since i > 0, there's at least one topping on the left.
            // Also i < intervals.size, so there is at least one topping on the right.
            return true;
        }
        // Otherwise, merge intervals (conceptually)
        maxEndX = max(maxEndX, intervals[i].second);
    }
    
    // No gap found
    return false;
}

int main() {
    // Example from the prompt:
    // a (0,6,0,1); b (7,8,0,4); c (0,1,2,4)
    vector<Topping> toppings = {
        {0, 6, 0, 1}, 
        {7, 8, 0, 4}, 
        {0, 1, 2, 4}
    };
    
    bool result = canMakeVerticalCut(toppings);
    cout << (result ? "True" : "False") << endl; // Expected: True

    return 0;
}
