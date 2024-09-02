class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // unordered_map<int,int> mpp;
        // int n = s.size();
        // int l =0,r = 0;
        // int maxi =0;
        // while(r<n){
        //     int c = s[r]-'a';
        //     if(mpp.find(c)!=mpp.end()){
        //         l = max(l,mpp[c]+1);
        //     }
        //     mpp[c] = r;
        //     maxi = max(maxi,r-l+1);
        //     r++;
        // }
        // return maxi;

        int n = s.size();
        int maxi =0;
        unordered_set<int> st;
        int l=0;
        for(int r=0;r<n;r++){
            if(st.find(s[r]-'a')!=st.end()){
                while(l<r && st.find(s[r]-'a')!=st.end()){
                    st.erase(s[l]-'a');
                    l++;
                }
            }
            st.insert(s[r]-'a');
            maxi = max(maxi,r-l+1);
        }
        return maxi;


    }
};