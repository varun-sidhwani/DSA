https://leetcode.com/discuss/interview-question/4874329/Google-onsite-Interview-question


int maxCustomer(vector<int> trans, int init){
	
	int threshold = -1 * init;

	int l = 0;
	int r = 0;

	int res = 0;

	int currSum = 0;


	while(r < trans.size()){

        currSum += trans[r];

        while(l <= r && currSum < threshold){

            currSum -= trans[l];
            l += 1;

        }

        res = max(res, r - l + 1);
		r += 1;
    }


    return res;
}
