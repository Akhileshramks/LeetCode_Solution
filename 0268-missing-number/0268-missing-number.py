class Solution:
    def missingNumber(self, nums: List[int]) -> int:
        n = len(nums)
        sum_original = sum(nums)
        sum_cal = n*(n+1)//2
        return sum_cal - sum_original