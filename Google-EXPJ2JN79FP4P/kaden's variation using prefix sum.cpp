
https://leetcode.com/discuss/interview-question/4929501/Google-onsite-Interview

This can be solved using a hash table to store prefix_sum for 
every number encountered. When meeting the same number already 
stored in the hash table update the result: res=max(res, sum-pre_fix_sum). 
Also update the value stored in the hash table for this number: pre_fix_sum=min(pre_fix_sum, sum).
The idea is that we always want the smallest pre_fix_sum, by doing so it can maximize the result.



vector<int> maxSumSubarray(vector<int> &nums);


int main() {
    std::cout << "Hello World!\n";
    
    // vector<int> nums = {1, 3, 5, 6, 3, -6, 3};
        vector<int> nums = {3, -6, -6, 10,3};

    
    vector<int> res = maxSumSubarray(nums);
    
    for(auto &n : res)
        cout<<n<<" ";
        
}

vector<int> maxSumSubarray(vector<int> &nums){

    int currSum = 0;
    int res = INT_MIN;
    int start  = -1;
    int end = -1;
    unordered_map<int, pair<int, int>> prefixSeen;



    for(int i = 0; i < nums.size(); i++){

        currSum += nums[i];

        if(prefixSeen.find(nums[i]) != prefixSeen.end()){

            int currSubarraySum = currSum - prefixSeen[nums[i]].first;


            if(res < currSubarraySum){
                res = currSubarraySum;
                start =  prefixSeen[nums[i]].second;
                end =  i;
            }

            if(currSum < prefixSeen[nums[i]].first){
                prefixSeen[nums[i]] = {currSum, i};
            }
        }

        else{
            prefixSeen.insert({nums[i], {currSum, i}});

        }

    }

    return vector<int>{start, end};
}
