https://leetcode.com/discuss/interview-question/5748871/Google-or-Question - 
Last Round

// Structure to represent a rectangle
struct Rectangle {
    double x1, y1, x2, y2;
};

// Function to calculate the total area of rectangles
double calculateTotalArea(const vector<Rectangle>& rectangles) {
    double totalArea = 0;
    for (const auto& rect : rectangles) {
        totalArea += (rect.x2 - rect.x1) * (rect.y2 - rect.y1);
    }
    return totalArea;
}

// Function to find the vertical line dividing the rectangles equally
double findDividingLine(const vector<Rectangle>& rectangles) {
    vector<double> xCoords;
    for (const auto& rect : rectangles) {
        xCoords.push_back(rect.x1);
        xCoords.push_back(rect.x2);
    }

    // Sort and remove duplicates
    sort(xCoords.begin(), xCoords.end());
    xCoords.erase(unique(xCoords.begin(), xCoords.end()), xCoords.end());

    double totalArea = calculateTotalArea(rectangles);
    double halfArea = totalArea / 2.0;
    double cumulativeArea = 0.0;

    // Sweep line algorithm
    for (size_t i = 0; i < xCoords.size() - 1; ++i) {
        double x = xCoords[i];
        double nextX = xCoords[i + 1];
        double width = nextX - x;

        // Calculate the area contribution of rectangles in this interval
        for (const auto& rect : rectangles) {
            if (rect.x1 <= x && rect.x2 > x) { // Rectangle intersects the interval
                double intersectHeight = rect.y2 - rect.y1;
                cumulativeArea += width * intersectHeight;
            }
        }

        // Check if the cumulative area equals half the total area
        if (cumulativeArea >= halfArea) {
            return x;
        }
    }

    // If no exact line is found, return -1 (error case)
    return -1;
}

int main() {
    vector<Rectangle> rectangles = {
        {1, 1, 4, 5}, 
        {2, 2, 6, 6}, 
        {3, 1, 7, 4}
    };

    double dividingLine = findDividingLine(rectangles);
    if (dividingLine != -1) {
        cout << "The dividing line is x = " << dividingLine << endl;
    } else {
        cout << "No dividing line found." << endl;
    }

    return 0;
}
