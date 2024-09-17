class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();
        if(n%groupSize != 0) return false;
        sort(hand.begin(),hand.end());
        vector<bool> visited(n,false);
        for(int i = 0;i<n;i++){
            if(!visited[i]){
                int k = i;
                int m = 0;
                while(k<n && m < groupSize){
                    if(!visited[k] && hand[i] + m == hand[k]){
                        visited[k] = true;
                        m++;
                        cout<<hand[k]<<" ";
                    }
                    k++;
                }
                cout<<endl;
                if(m!= groupSize){
                    cout<< hand[i]<<endl;
                    return false;
                }
            }
        }
        return true;
    }
};

/*

1   2   2   3   3   4   6   7   8

*/