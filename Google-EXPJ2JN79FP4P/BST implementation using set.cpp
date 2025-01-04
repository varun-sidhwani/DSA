
https://leetcode.com/discuss/interview-question/4964533/Google-Phone-Interview-Question

/*

Q: There is stream of float values (-inf, inf) which is coming as input and an integer D.

We need to find a set of 3 values which satisfy condition - |a - b| <= D, |b - c| <= D, |a - c| <= D, 
assuming a,b,c are 3 float values. Print these 3 values and remove them and continue ....

Constraints -
All values in stream will be unique.
D -> [0, inf)

Eg:
Input stream - [1,10,7,-2,8,....], d = 5
Output - (when 8 comes, then print "7 8 10" and remove them and continue)

*/



class Solution {
    private int D;
    private TreeSet<Float> nums;

    // TC - O(1)
    void init(int d) {
        this.D = d;
        nums = new TreeSet<>();
    }

    // Helper method to check and remove a valid triplet
    private boolean checkAndRemoveTriplet(Float a, Float b, Float c) {
        if (a != null && b != null && c != null && Math.abs(b - a) <= D && Math.abs(c - b) <= D) {
            nums.remove(a);
            nums.remove(b);
            nums.remove(c);
            return true;
        }
        return false;
    }

    // TC - O(logN)
    void func(float item) {
        // Check if item is the middle element in a triplet
        Float a = nums.floor(item);
        Float c = nums.ceiling(item);
        if (checkAndRemoveTriplet(a, item, c)) return;

        // Check if item is the first element in a triplet
        a = nums.ceiling(item);
        c = a != null ? nums.ceiling(a) : null;
        if (checkAndRemoveTriplet(item, a, c)) return;

        // Check if item is the third element in a triplet
        a = nums.floor(item);
        c = a != null ? nums.floor(a) : null;
        if (checkAndRemoveTriplet(c, a, item)) return;
    }
}
