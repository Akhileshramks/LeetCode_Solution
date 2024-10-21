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
    ListNode* KthNode(ListNode* head,int k){
        ListNode* temp = head;
        k -= 1;
        while(k && temp){
            temp = temp->next;
            k--;
        }
        return temp;
    }
    ListNode* reverse(ListNode* head){
        ListNode* temp = head;
        ListNode* prev = NULL;
        while(temp){
            ListNode* nxt = temp->next;
            temp->next = prev;
            prev = temp;
            temp = nxt;
        }
        return prev;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* temp = head;
        ListNode* prevnode = NULL;
        while(temp){
            ListNode* Knode = KthNode(temp,k);
            if(Knode == NULL){
                if(prevnode) prevnode->next = temp;
                break;
            }
            ListNode* nxtNode = Knode->next;
            Knode->next = NULL;
            ListNode* newHead = reverse(temp);
            if(temp == head) head = newHead;
            else prevnode->next = newHead;
            prevnode = temp;
            temp = nxtNode;
        }
        return head;
    }
};