class Solution:
    def survivedRobotsHealths(self, positions: List[int], healths: List[int], directions: str) -> List[int]:
        n = len(positions)
        robot = [[positions[ind],healths[ind],directions[ind],ind] for ind in range(n)]
        robot.sort()

        st = []
        for i in robot:
            if(i[2] == "R" or not st or st[-1][2] == "L"):
                st.append(i)
                continue
            
            elif(i[2] == "L"):
                add = True
                while(st and st[-1][2] == "R" and add):
                    m = st[-1]
                    if(m[1]>i[1]):
                        st[-1][1]-=1
                        add = False
                    elif(m[1]<i[1]):
                        i[1]-=1
                        st.pop()
                    else:
                        st.pop()
                        add = False
                if(add):
                    st.append(i)
        st.sort(key=lambda x:x[-1])
        ls = []
        for i in st:
            ls.append(i[1])
        return ls