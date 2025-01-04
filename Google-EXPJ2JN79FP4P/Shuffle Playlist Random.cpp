https://leetcode.com/discuss/interview-question/2337984/Google-or-Onsite-or-Song-Shuffler
https://leetcode.com/problems/insert-delete-getrandom-o1/description/
https://leetcode.com/problems/random-pick-with-weight/description/
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

class SongShuffler {
private:
    std::queue<std::string> lastPlayed;  // Queue to track the last 'k' songs played
    std::vector<std::string> songs;      // List of songs not played in the last 'k' turns
    int k;                               // Number of turns to restrict a song from being replayed

public:
    // Constructor
    SongShuffler(const std::vector<std::string>& playlist, int k) : songs(playlist), k(k) {
        std::srand(std::time(nullptr)); // Seed the random number generator
    }

    // Play the next song
    std::string playNext() {
        if (songs.empty()) {
            throw std::runtime_error("No songs available to play.");
        }

        // Generate a random index
        int randomIndex = std::rand() % songs.size();

        // Get the song at the random index
        std::string nextSong = songs[randomIndex];

        // Replace the random index song with the last song in the list
        songs[randomIndex] = songs.back();
        songs.pop_back(); // Remove the last song (now duplicated at randomIndex)

        // Add the played song to the queue
        lastPlayed.push(nextSong);

        // If the queue exceeds 'k', move the oldest song back to the songs list
        if (lastPlayed.size() > k) {
            songs.push_back(lastPlayed.front());
            lastPlayed.pop();
        }

        return nextSong;
    }
};

int main() {
    // Example usage
    std::vector<std::string> playlist = {"A", "B", "C", "D"};
    int k = 2;

    SongShuffler shuffler(playlist, k);

    for (int i = 0; i < 10; ++i) {
        std::cout << "Next song: " << shuffler.playNext() << std::endl;
    }

    return 0;
}
