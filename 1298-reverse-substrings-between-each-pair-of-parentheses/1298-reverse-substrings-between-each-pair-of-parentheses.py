from collections import deque
class Solution:
    def reverseParentheses(self, s: str) -> str:
        st = deque()
        q = deque()
        m=""
        for i in s:

            if(i==')'):
                while True:
                    p = st.pop()
                    if(p=="("): 
                        break
                    q.append(p)
                while(q):
                    st.append(q.popleft())
                print(st)
            else:
                st.append(i)
                

        while(st):
            m+=st.popleft()
        return m