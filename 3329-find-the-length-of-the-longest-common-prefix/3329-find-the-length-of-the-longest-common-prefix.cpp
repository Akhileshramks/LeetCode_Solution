class Trie_Node{
    public:
    Trie_Node* arr[10];
    Trie_Node(){
        for(int i =0;i<10;i++) arr[i] = NULL;
    }
};

class Trie{
    public:
    Trie_Node* root;
    Trie(){
        root = new Trie_Node();
    }
    void insert(string val){
        Trie_Node* root1 = root;
        int m = val.size();
        for(int i =0;i<m;i++){
            int ind = val[i]-'0';
            if(root1->arr[ind] == NULL){
                root1->arr[ind] = new Trie_Node();
            }
            root1 = root1->arr[ind];
        }
    }
    int search(string pat){
        Trie_Node* root1 = root;
        int p = pat.size();
        int count =0;
        for(int i =0;i<p;i++){
            int ind = pat[i]-'0';
            if(root1->arr[ind] == NULL){
                return count;
            }
            root1 = root1->arr[ind];
            count++;
        }
        return count;
    }
};


class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        Trie* root = new Trie();
        for(int s : arr2){
            root->insert(to_string(s));
        }
        int maxi = 0;
        for(int s : arr1){
            maxi =max(maxi,root->search(to_string(s)));
        }
        return maxi;
    }
};