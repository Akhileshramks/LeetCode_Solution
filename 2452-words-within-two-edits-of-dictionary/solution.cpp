class TrieNode{
    public:
        vector<TrieNode*> child;
        bool isEnd;
        TrieNode(){
            child = vector<TrieNode*>(26, nullptr);
            isEnd = false;
        }
};
class Trie{
    public:
        TrieNode* root;
        Trie(){
            root = new TrieNode();
        }
        void insert(string s){
            TrieNode* root_node = root;
            for(char c: s){
                int ind = c-'a';
                if(root_node->child[ind] == nullptr){
                    root_node->child[ind] = new TrieNode();
                }
                root_node = root_node->child[ind];
            }
            root_node->isEnd = true;
        }
        bool dfs(string s,int ind,int count, TrieNode* root_node,int maxLimit){
            if(count > maxLimit) return false;
            bool isPossible = false;
            int i = s[ind] - 'a';
            if(root_node->isEnd == true) return true;
            for(int j = 0;j < 26 && !isPossible;j++){
                if(root_node->child[j] != nullptr){
                    if(i == j) isPossible |= dfs(s,ind+1,count, root_node->child[j],maxLimit);
                    else isPossible |= dfs(s,ind+1,count+1, root_node->child[j],maxLimit);
                }
            }
            return isPossible;
        }
        bool callDFS(string s, int maxLimit){
            return dfs(s,0,0,root,maxLimit);
        }
};
class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        Trie trie;
        for(string s : dictionary){
            trie.insert(s);
        }
        vector<string> res;
        for(string s: queries){
            if(trie.callDFS(s, 2)){
                res.push_back(s);
            }
        }
        return res;
    }
};