https://chatgpt.com/share/6777d5df-c158-8003-bd9a-4b5250e494a2 - for followup 1 & 2 

Part 1: Reservoir Sampling for Streams
Reservoir sampling is inherently designed for streams, so no changes are necessary. 
You simply process each incoming user one by one without storing all of them.


string reservoirSamplingStream(istream& stream) {
    string selectedUser, user;
    int count = 0;

    while (stream >> user) { // Assume the stream provides one user at a time
        count++;
        // Replace the selected user with probability 1/count
        if (rand() % count == 0) {
            selectedUser = user;
        }
    }

    return selectedUser;
}


Key Insight: Uniform Probability
In reservoir sampling, each incoming user has an equal chance of being the selected user. Specifically:

First user: Always selected (probability = 1).
Second user: Replaces the first user with 1/2 probability.
Third user: Replaces the current selection with 1/3 probability, meaning it has 1/3 probability, while the previous selections have adjusted probabilities.
Nth user: Replaces the current selection with 1/n probability.
This ensures that all users have a final probability of 1/n, where n is the total number of users processed so far.

string mostActiveUserUntilTStream(istream& stream, int t) {
    unordered_map<string, int> userActivity;
    string user;
    int timestamp;

    while (stream >> user >> timestamp) { // Read user and timestamp from stream
        if (timestamp > t) {
            break; // Stop processing once time t is exceeded
        }
        userActivity[user]++;
    }

    string mostActiveUser;
    int maxCount = 0;

    for (const auto& [user, count] : userActivity) {
        if (count > maxCount) {
            maxCount = count;
            mostActiveUser = user;
        }
    }

    return mostActiveUser;
}

vector<pair<string, int>> topKActiveUsersUntilTStream(istream& stream, int t, int k) {
    unordered_map<string, int> userActivity;
    string user;
    int timestamp;

    while (stream >> user >> timestamp) {
        if (timestamp > t) {
            break; // Stop processing once time t is exceeded
        }
        userActivity[user]++;
    }

    // Use a min-heap to track the top k active users
    auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second; // Min-heap based on activity count
    };
    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> minHeap(cmp);

    for (const auto& [user, count] : userActivity) {
        minHeap.push({user, count});
        if (minHeap.size() > k) {
            minHeap.pop(); // Maintain heap size
        }
    }

    // Extract the top k users from the heap
    vector<pair<string, int>> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }

    // Sort the result by activity count in descending order
    sort(result.begin(), result.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return b.second > a.second; // Descending order
    });

    return result;
}