class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        long long sum = accumulate(arr.begin(),arr.end(),0ll);
        if(sum % k != 0) return false;
        sort(arr.begin(),arr.end(),[&](const int &a,const int &b){
            return (k+a%k)%k < (k+b%k)%k;
        });
        int start = 0;
        int end = arr.size() - 1;
        while(start < end){
            if(arr[start] % k == 0){
                if(arr[start + 1] % k == 0){
                    start += 2;
                    continue;
                }
                else{
                    return false;
                }
            }
            else{
                break;
            }
        }
        while(start < end){
            if((arr[start] + arr[end])%k == 0){
                start++;
                end--;
            }
            else{
                return false;
            }
        }
        return true;
    }
};