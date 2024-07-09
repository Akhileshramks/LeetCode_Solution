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
        ListNode sum;
        ListNode* head = &sum;
        ListNode* res = &sum;
        int carry =0;
        int sum_ind,l1_val,l2_val;
        while(l1!=nullptr || l2!=nullptr || carry!=0){
            l1_val = l1!=nullptr ? l1->val : 0;
            l2_val = l2!=nullptr ? l2->val :0;
            sum_ind = l1_val+l2_val+carry;
            carry = sum_ind/10;
            sum_ind = sum_ind%10;
            head->next = new ListNode(sum_ind);
            head = head->next;
            l1 = l1!=nullptr ? l1->next : nullptr;
            l2 = l2!=nullptr ? l2->next : nullptr;
        }
        return res->next;
    }
};