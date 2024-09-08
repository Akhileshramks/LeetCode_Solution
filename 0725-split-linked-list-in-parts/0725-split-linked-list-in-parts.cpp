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
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        ListNode* temp = head;
        vector<ListNode*> res(k);
        int count = 0;
        while(temp){
            temp = temp -> next;
            count++;
        }
        if(count == 0) return res;
        int n = count / k;
        int rem = count % k;
        
        ListNode* current  = head;
        ListNode* prev = NULL;
        for(int i =0;i<k;i++){
            int m = n;
            if(rem){
                m += 1;
                rem--;
            }
            res[i] = current;
            while(current && m){
                prev = current;
                current = current-> next;
                m--;
            }
            prev->next = NULL;
        }
        return res;
    }
};