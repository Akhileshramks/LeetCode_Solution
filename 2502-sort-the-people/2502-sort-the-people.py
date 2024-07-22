class Solution:
    def sortPeople(self, names: List[str], heights: List[int]) -> List[str]:
        ls = list(zip(heights,names))
        ls.sort(reverse=True)
        return [i[1] for i in ls]