class Solution {
public:

    int maxSplit(string s,int start,set<string>& st){
        int maxi = 0;
        if(start == s.size()) return 0;
        for(int i = start+1; i <= s.size();i++){
            string newString = s.substr(start,i-start);
            if(st.find(newString) == st.end()){
                st.insert(newString);
                maxi = max(maxSplit(s,i,st)+1,maxi);
                st.erase(newString);
            }
        }
        return maxi;
    }
    int maxUniqueSplit(string s) {
        set<string> st;
        return maxSplit(s,0,st);
    }
};