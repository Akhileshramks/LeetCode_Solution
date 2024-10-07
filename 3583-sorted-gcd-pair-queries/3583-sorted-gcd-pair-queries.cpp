class Solution {
public:

    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int maxLen = *max_element(nums.begin(),nums.end())+1;
        vector<long long> divisorCount(maxLen,0);
        for(int &n : nums){
            for(int i = 1; i*i <= n; i++){
                if(n % i == 0){
                    divisorCount[i]++;
                    if( i != n/i){
                        divisorCount[(n/i)]++;
                    }
                }
            }
        }

        for(int i = maxLen-1;i >= 1;i--){
            divisorCount[i] = 1ll*(divisorCount[i]*(divisorCount[i]-1)/2);
            for(int j = 2*i;j<maxLen;j+=i){
                divisorCount[i] -= divisorCount[j];
            }   
        }

        vector<long long> prefix(maxLen,0);
        for(int i = 1; i < maxLen;i++){
            prefix[i] = prefix[i-1] + divisorCount[i];
        }

        vector<int> res;
        for(auto &k : queries){
            long long low = 0;
            long long high = maxLen-1;
            long long ans = -1;
            while(low <= high){
                long long mid = low + (high-low)/2;
                if(prefix[mid] > k){
                    high = mid-1;
                    ans = mid;
                }
                else{
                    low = mid+1;
                }
            }
            res.push_back(ans);
        }
        return res;

    }
};