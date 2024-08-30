class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(),wordList.end());
        if(words.find(endWord) == words.end()) return 0;
        queue<string> q;
        q.push(beginWord);
        int ans = 1;
        while(!q.empty()){
            int size = q.size();
            ans++;
            while(size--){
                string p = q.front();
                q.pop();
                string original = p;
                int n = p.size();
                for(int i=0;i<n;i++){
                    for(char j = 'a';j<='z';j++){
                        p[i] = j;
                        if(p == endWord) return ans;
                        if(words.find(p)!=words.end()){
                            q.push(p);
                            words.erase(p);
                        }
                    }
                    p = original;
                }
            }    
        }
        return 0;
    }
};