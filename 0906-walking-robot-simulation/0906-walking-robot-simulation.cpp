class Solution {
public:
    int hashFunction(pair<int,int> p){
        int multiplier = 60013;
        return p.second*multiplier+p.first;
    }
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        vector<pair<int,int>> directions = {{0,1},{1,0},{0,-1},{-1,0}};
        int currDirection = 0;
        unordered_set<int> st;
        for(auto i : obstacles){
            st.insert(hashFunction({i[0],i[1]}));
        }
        int current_x = 0;
        int current_y = 0;
        int maxi = 0;
        for(auto i : commands){
            if( i == -1 ){
                currDirection = (currDirection+1)%4;
                continue;
            }
            else if( i == -2){
                currDirection = (currDirection+3)%4;
                continue;
            }
            int inc_x = directions[currDirection].first;
            int inc_y = directions[currDirection].second;
            int new_current_x = current_x;
            int new_current_y = current_y;
            for(int k = 0;k<i;k++){
                new_current_x += inc_x;
                new_current_y += inc_y;
                if(st.find(hashFunction({new_current_x,new_current_y}))!=st.end()){
                    break;
                }
                current_x = new_current_x;
                current_y = new_current_y;
                maxi = max(maxi,current_x*current_x+current_y*current_y);
            }
           
        }
        return maxi;
    }
};

/*

direction = [0,1]
(0,1) => y = y+4
(1,0) => x = x+4
(0,-1)) => y = y-4
(-1,0) => x = x-4
*/