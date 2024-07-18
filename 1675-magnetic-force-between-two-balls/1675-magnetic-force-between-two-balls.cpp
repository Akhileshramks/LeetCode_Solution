class Solution {
public:
    int possible(vector<int>& position,int d){
        int n = position.size();
        int curr = position[0];
        int count = 1;
        for(int i=1;i<n;i++){
            if(curr+d<=position[i]){
                count++;
                curr = position[i];
            }
        }
        return count;
    }
    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(),position.end());
        int n = position.size();
        int low = 1;
        int high = position[n-1]-position[0];
        while(low<=high){
            int mid = low+(high-low)/2;
            int p = possible(position,mid);
            if(p<m){
                high = mid-1;
            }
            else{
                low= mid+1;
            }
        }
        return high;
    }
};