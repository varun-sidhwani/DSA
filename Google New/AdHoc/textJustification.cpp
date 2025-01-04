class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        vector<string> line;
        int lineLength = 0;
        int i = 0;

        while (i < words.size()) {
            // Check if adding the current word exceeds the maxWidth
            if (lineLength + line.size() + words[i].length() > maxWidth) {
                // Distribute spaces
                int extraSpaces = maxWidth - lineLength;
                int spaces = (line.size() == 1) ? extraSpaces : extraSpaces / (line.size() - 1);
                int remainder = (line.size() == 1) ? 0 : extraSpaces % (line.size() - 1);

                string justifiedLine;
                for (int j = 0; j < line.size(); ++j) {
                    justifiedLine += line[j];
                    if (j < line.size() - 1) {
                        justifiedLine += string(spaces, ' ');
                        if (remainder > 0) {
                            justifiedLine += " ";
                            remainder--;
                        }
                    }
                }
                // Add remaining spaces for a single word line
                if (line.size() == 1) justifiedLine += string(extraSpaces, ' ');

                result.push_back(justifiedLine);
                line.clear();
                lineLength = 0;
            }

            // Add the current word to the line
            line.push_back(words[i]);
            lineLength += words[i].length();
            i++;
        }

        // Handle the last line (left-justified)
        string lastLine;
        for (int j = 0; j < line.size(); ++j) {
            if (j > 0) lastLine += " ";
            lastLine += line[j];
        }
        lastLine += string(maxWidth - lastLine.length(), ' ');
        result.push_back(lastLine);

        return result;
    }
};

////


    vector<string> words;
    stringstream ss(text);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }


/////