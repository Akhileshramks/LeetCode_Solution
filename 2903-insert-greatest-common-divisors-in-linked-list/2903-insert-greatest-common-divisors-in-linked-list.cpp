class Solution {
public:
    int gcd(int a,int b){
        if(b==0) return a;
        return gcd(b,a%b);
    }
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* temp = head;
        ListNode* prev;
        while(temp->next){
            prev = temp;
            temp = temp->next;
            ListNode* new_node = new ListNode(gcd(prev->val,temp->val));
            new_node->next = temp;
            prev->next = new_node;
        }
        return head;
    }
};