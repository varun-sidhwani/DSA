

#include <queue>
#include <vector>

class MedianFinder {
private:
    std::priority_queue<int> maxHeap; // Max-heap for the smaller half
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // Min-heap for the larger half

public:
    MedianFinder() {}

    // Adds a number into the data structure
    void addNum(int num) {
        // Step 1: Add to maxHeap
        maxHeap.push(num);

        // Step 2: Balance - move the largest from maxHeap to minHeap
        minHeap.push(maxHeap.top());
        maxHeap.pop();

        // Step 3: Ensure maxHeap has at least as many elements as minHeap
        if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        // If maxHeap has more elements, the median is the top of maxHeap
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        }
        // If heaps are balanced, the median is the average of the tops
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};
