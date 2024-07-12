class Solution:
    def remove_ab(self, s, p):
        st = []
        for i in s:
            if(st and st[-1]==p[0] and i==p[1]):
                st.pop()
            else:
                st.append(i)
        return ''.join(st)
    def maximumGain(self, s: str, x: int, y: int) -> int:
        if(x>y):
            higher_p = "ab"
            lesser_p = "ba"
        else:
            higher_p = "ba"
            lesser_p = "ab"
            x,y = y,x
        n = len(s)
        new_s = self.remove_ab(s,higher_p)
        cost =  ((n-len(new_s))//2)*x
        new_S = self.remove_ab(new_s,lesser_p)
        cost += ((len(new_s)-len(new_S))//2)*y
        return cost
        