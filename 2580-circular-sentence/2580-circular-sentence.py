class Solution:
    def isCircularSentence(self, sentence: str) -> bool:
        ls = list(sentence.split());
        n = len(ls)
        for i in range(1,n):
            if(ls[i-1][-1] != ls[i][0]):
                return False
        if(ls[-1][-1] != ls[0][0]):
            return False
        return True