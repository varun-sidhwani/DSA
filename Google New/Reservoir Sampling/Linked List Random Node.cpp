https://leetcode.com/problems/linked-list-random-node

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
private:
    ListNode* head;

public:
    // Constructor
    Solution(ListNode* head) {
        this->head = head;
    }
    
    // Returns a random node's value
    int getRandom() {
        int reservoir = -1;
        int i = 0; // Index to track the position in the list
        ListNode* current = head;

        while (current != nullptr) {
            // Replace the reservoir with probability 1 / (i + 1)
            if (rand() % (i + 1) == 0) {
                reservoir = current->val;
            }
            current = current->next;
            i++;
        }

        return reservoir;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */