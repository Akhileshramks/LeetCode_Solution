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
class comp{
    public:
        bool operator()(ListNode* a,ListNode* b){
            return a->val > b->val;
        }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<ListNode*> ans;
        priority_queue<ListNode*,vector<ListNode*>,comp> pq;
        for(auto &head : lists){
            if(head) pq.push(head);
        }
        ListNode* dummy = new ListNode(-1);
        ListNode* head = dummy;
        while(!pq.empty()){
            head -> next = pq.top();
            pq.pop();
            head = head -> next;
            if(head->next){
                pq.push(head->next);
            }
        }
        return dummy->next;
    }
};