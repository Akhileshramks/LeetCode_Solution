class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        d = {i:-1 for i in range(256)}
        l = 0
        r = 0
        n = len(s)
        maxi = 0
        while(r<n):
            m = d[ord(s[r])]
            if(m!=-1):
                l = max(m+1,l)
            d[ord(s[r])] = r
            maxi = max(maxi,r-l+1)
            r+=1
        return maxi

        