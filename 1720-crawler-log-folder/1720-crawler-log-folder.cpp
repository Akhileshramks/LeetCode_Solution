class Solution {
public:
    int minOperations(vector<string>& logs) {
        string curr = "/" ;
        int count = 0 ;
        for(auto i:logs){
            if(i.compare("../")==0){
                count = count==0 ? 0 : count-1;
            }
            else if(i.compare("./")==0){
                count = count;
            }
            else{
                count +=1;
                curr = i;
            }
        }
        return count;
    }
};