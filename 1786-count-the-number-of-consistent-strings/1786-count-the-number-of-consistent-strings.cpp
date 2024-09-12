class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        unordered_set<char> st;
        int count = 0;
        for(char i : allowed) st.insert(i);
        bool flag = true;
        for(int i =0;i<words.size();i++){
            flag = true;
            for(char i : words[i]){
                if(st.find(i) == st.end()){
                    flag = false;
                    break;
                }
            }
            if(flag) count++;
        }
        return count;
    }
};