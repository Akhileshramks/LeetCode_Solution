from collections import deque
class Solution(object):
    def removeKdigits(self, num, k):
        """
        :type num: str
        :type k: int
        :rtype: str
        """
        stack = []
        for i in num:
            while(stack and k>0 and stack[-1]>i):
                k -= 1
                stack.pop()
            stack.append(i)
        stack = stack[:-k] if(k>0) else stack
        s = ''.join(stack)
        s = s.lstrip('0')
        return "0" if(len(s)==0) else s
        