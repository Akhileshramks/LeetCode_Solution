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
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        int top = 0,bottom = m-1,left = 0,right = n-1;
        vector<vector<int>> matrix(m,vector<int>(n,-1));
        while(top<=bottom && left<=right && head){
            for(int i =left;i<=right;i++){
                matrix[top][i] = head ? head->val : -1;
                head = head ? head->next : head;
            }
            top++;
            for(int i = top;i<=bottom;i++){
                matrix[i][right] = head ? head->val : -1;
                head = head ? head->next : head;
            }
            right--;
            if(top<=bottom){
                for(int i = right;i>=left;i--){
                    matrix[bottom][i] = head ? head->val : -1;
                    head = head ? head->next : head;
                }
                bottom--;
            }
            if(left<=right){
                for(int i = bottom;i>=top;i--){
                    matrix[i][left] = head ? head->val : -1;
                    head = head ? head->next : head;
                }
                left++;
            }
        }
        return matrix;
    }
};