class Solution(object):
    def passThePillow(self, n, time):
        """
        :type n: int
        :type time: int
        :rtype: int
        """

        m = time//(n-1)
        if(m%2 == 0):
            return (time%(n-1)+1)
        else:
            return (n-(time%(n-1)))
        