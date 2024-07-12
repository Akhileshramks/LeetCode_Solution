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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* temp = head;
        int count = 0;
        while(temp){
            temp = temp->next;
            count+=1;
        }
        ListNode dummy(0);
        ListNode* res = &dummy;
        ListNode* ans = res;
        res->next = head;
        while(count>=k){
            ListNode* current = res->next;
            ListNode* last = res->next;
            ListNode* prev = NULL;
            for(int i=0;i<k;i++){
                ListNode* nxt = current->next;
                current->next = prev;
                prev = current;
                current = nxt;
            }
            count-=k;
            last->next = current;
            res->next = prev;
            res = last;
        }
        return ans->next;
    }
};