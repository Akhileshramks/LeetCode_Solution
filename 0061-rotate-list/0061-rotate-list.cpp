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
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || k==0) return head;
        int count = 0;
        ListNode* temp = head;
        ListNode* end;
        ListNode* prev;
        while(temp){
            end = temp;
            temp = temp->next;
            count+=1;
        }
        k = k%count;
        if(k==0){
            return head;
        }
        k = count-k;
        temp = head;
        while(k){
            prev = temp;
            temp = temp->next;
            k--;
        }
        prev->next = NULL;
        end->next = head;
        return temp;
    }
};