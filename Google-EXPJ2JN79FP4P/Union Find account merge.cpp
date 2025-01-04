https://leetcode.com/discuss/interview-question/5014822/Google-Phone-Screen-(SDE-II-US)

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    int n = accounts.size();
    UnionFind uf(n);
    unordered_map<string, int> emailToIndex;
    unordered_map<int, unordered_set<string>> indexToEmails;

    // Step 1: Map emails to their account indices
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < accounts[i].size(); ++j) {
            string email = accounts[i][j];
            if (emailToIndex.find(email) == emailToIndex.end()) {
                uf.unionSet(i, emailToIndex[email]);
            } else {
                emailToIndex[email] = i;
            }
        }
    }

    // Step 2: Group emails by their parent index
    for (const auto& [email, index] : emailToIndex) {
        int leader = uf.find(index);
        indexToEmails[leader].insert(email);
    }

    // Step 3: Prepare the result
    vector<vector<string>> res;
    for (const auto& [index, emails] : indexToEmails) {
        vector<string> mergedAccount;
        mergedAccount.push_back(accounts[index][0]); // Add account name
        mergedAccount.insert(mergedAccount.end(), emails.begin(), emails.end());
        sort(mergedAccount.begin() + 1, mergedAccount.end()); // Sort emails
        res.push_back(mergedAccount);
    }

    return res;
}
