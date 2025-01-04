https://leetcode.com/discuss/interview-question/6089146/Google-Interview-Experience-or-Stuck-in-this-problem-or-need-Help



#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;  // Number of videos, number of tags per video

    vector<vector<int>> videoTags(N, vector<int>(K));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            cin >> videoTags[i][j];
        }
    }

    // Map from tag to a list of videos that contain this tag
    unordered_map<int, vector<int>> tagToVideos;

    for (int i = 0; i < N; i++) {
        set<int> similarVideos;  // Use a set to store unique similar videos

        // Check each tag of the current video
        for (int tag : videoTags[i]) {
            // If the tag exists in the map, add all earlier videos to the similarity set
            if (tagToVideos.count(tag)) {
                for (int vid : tagToVideos[tag]) {
                    if (vid < i) {  // Only consider videos with indices < i
                        similarVideos.insert(vid);
                    }
                }
            }
            // Add the current video to the list of videos for this tag
            tagToVideos[tag].push_back(i);
        }

        // Output the similar videos for the current video
        cout << "Similar videos for " << i << ": ";
        for (int vid : similarVideos) {
            cout << vid << " ";
        }
        cout << "\n";
    }

    return 0;
}
