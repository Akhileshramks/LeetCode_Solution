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
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode* dummy = new ListNode(0);
        ListNode* res = dummy;
        while(l1 || l2 || carry){
            int l1Val= l1 ? l1->val : 0;
            int l2Val = l2 ? l2->val : 0;
            int sum = l1Val + l2Val + carry;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
            carry = sum/10;
            sum = sum%10;
            res->next = new ListNode(sum);
            res = res->next;
        }
        return dummy->next;
    }
};