class Trie_Node{
    public:
        Trie_Node* children[26];
        int prefix_count;
        Trie_Node(){
            for(int i = 0;i <26; i++) children[i] = NULL;
            prefix_count = 0;
        }
};

class Trie {
    public:
        Trie_Node* root;
        Trie(){
            root = new Trie_Node();
        }
        void insert(string s){
            Trie_Node* curr = root;
            int n = s.size();
            for(int i =0; i <n; i++){
                int ind = s[i] - 'a';
                if(curr->children[ind] == NULL){
                    curr->children[ind] = new Trie_Node();
                }
                curr = curr->children[ind];
                curr->prefix_count++;
            }
        }
        int search(string s){
            Trie_Node* curr = root;
            int n = s.size();
            int total = 0;
            for(int i =0;i<n;i++){
                int ind = s[i] - 'a';
                if(curr->children[ind] == NULL) break;
                curr = curr->children[ind];
                total += curr->prefix_count;
            }
            return total;
        }
};
class Solution {
public:
    vector<int> sumPrefixScores(vector<string>& words) {
        Trie* prefixTree = new Trie();
        for(string s : words) prefixTree->insert(s);
        int n = words.size();
        vector<int> res(n,0);
        for(int i =0;i<n;i++){
            res[i] = prefixTree->search(words[i]);
        }
        return res;
    }
};