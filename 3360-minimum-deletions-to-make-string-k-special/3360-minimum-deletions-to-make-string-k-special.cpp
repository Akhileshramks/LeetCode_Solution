class Solution {
public:
    int assumeGivenCharMin(string word, int ind, vector<int>& freq, int k){
        int x = freq[ind];
        int del = 0;
        for(int i = 0;i < 26;i++){
            int y = freq[i];
            if(y < x) del += y;
            else if(y - x < k) continue;
            else del += y - x - k;
        }
        return del;
    }
    int minimumDeletions(string word, int k) {
        vector<int> freq(26);
        for(int i = 0;i < word.size(); i++){
            freq[word[i] - 'a']++;
        }
        int ans =  word.size();
        for(int i = 0;i < 26;i++){
            if(freq[i] > 0){
                ans = min(ans, assumeGivenCharMin(word,i,freq,k));
            }
        }
        return ans;

    }
};


/*

Case 1 : 
y < x => delete all y

Case 2 :
y > x =>
        1. y - x < k => no issue
        2. y - x > k => y - x - k characters need to be deleted

Case 3 :
 y == x no issues


 Time Complexity : O(n) + O(C)* O(C) => O(n + C^2)
 Space Complexity : O(C)
*/

