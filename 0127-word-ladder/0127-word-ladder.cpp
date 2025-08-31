class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(),wordList.end());
        if(st.find(endWord) == st.end()) return 0;

        queue<string> q;
        q.push(beginWord);
        int ans = 0;
        while(!q.empty()){
            int size = q.size();
            ans++;
            while(size--){
                string frontWord = q.front();
                q.pop();
                int len = frontWord.size();
                for(int ind = 0; ind < len; ind++){
                    char originalChar = frontWord[ind];
                    for(int i = 0;i < 26;i++){
                        char duplicateChar = 'a'+i;
                        if(originalChar != duplicateChar){
                            frontWord[ind] = duplicateChar;
                            if(frontWord == endWord) return ans + 1;
                            if(st.find(frontWord) != st.end()){
                                q.push(frontWord);
                                st.erase(frontWord);
                            }
                        }
                    }
                    frontWord[ind] = originalChar;
                }
            }
        }
        return 0;
    }
};