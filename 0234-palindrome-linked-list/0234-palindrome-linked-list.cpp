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
    ListNode* rotate(ListNode* head){
        ListNode* prev = nullptr;
        ListNode* current = head;
        while(current){
            ListNode* nxt = current->next;
            current->next = prev;
            prev = current;
            current = nxt;
        }
        return prev;
    }
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode* first = head;
        ListNode* second = rotate(slow);
        while(second){
            if(first && second && first->val==second->val){
                first = first->next;
                second = second->next;
            }
            else{
                return false;
            }
        }
        return true;
    }
};