

Now each ad also contains a delay(let's say 5, possibly different for each ad) with it which represents we can't 
server that ad until the next 5 ads. The previous question was a case with delay as 1 for each ad.
Solution: Use two heaps. After serving an ad, insert that in the new heap as insert the delay + ads served so far. 
And before serving any ad, check if any of the ads from the second heap can be inserted back in heap1 (basically the ads whose delay period has ended).

#include <iostream>
#include <queue>
#include <string>

using namespace std;

class AdServer {
private:
    priority_queue<pair<int, string>> adQueue; // Max-heap: (score, content)
    pair<int, string> lastServedAd;           // Last served ad
    bool hasLastAd;                           // To handle the first call to serveAd

public:
    AdServer() : hasLastAd(false) {}

    // Insert a new ad into the server
    void insertAd(const string& content, int score) {
        adQueue.push({score, content});
    }

    // Serve the best ad, ensuring no consecutive repeats
    string serveAd() {
        if (adQueue.empty()) {
            return "No ads available!";
        }

        // Temporarily hold the top ad
        pair<int, string> bestAd = adQueue.top();
        adQueue.pop();

        if (hasLastAd && bestAd.second == lastServedAd.second) {
            // If the best ad is the same as the last served ad
            if (adQueue.empty()) {
                // No other ads available
                adQueue.push(bestAd); // Put it back and return no ads
                return "No ads available!";
            }

            // Serve the next best ad
            pair<int, string> nextBestAd = adQueue.top();
            adQueue.pop();
            adQueue.push(bestAd); // Put the previous best ad back

            lastServedAd = nextBestAd; // Update last served ad
            return "Serving Ad: " + nextBestAd.second;
        }

        // Serve the current best ad
        lastServedAd = bestAd;
        hasLastAd = true;
        return "Serving Ad: " + bestAd.second;
    }
};

int main() {
    AdServer server;

    // Insert ads into the server
    server.insertAd("Ad1: Buy our product!", 50);
    server.insertAd("Ad2: Limited time offer!", 70);
    server.insertAd("Ad3: Best deals here!", 60);

    // Serve ads
    cout << server.serveAd() << endl; // Should serve Ad2
    cout << server.serveAd() << endl; // Should serve Ad3
    cout << server.serveAd() << endl; // Should serve Ad1
    cout << server.serveAd() << endl; // Should serve Ad2 again
    return 0;
}
