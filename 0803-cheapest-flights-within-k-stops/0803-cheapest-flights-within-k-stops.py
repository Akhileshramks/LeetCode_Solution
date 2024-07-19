class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, k: int) -> int:
        adj = collections.defaultdict(list)
        for start, end, price in flights:
            adj[start].append((price, end))
        
        q = collections.deque([(0, 0, src)])
        all_prices = [math.inf] * n

        while q:
            price, stops, cur = q.popleft()
            
            if stops >= k + 1:
                continue

            for nbr_price, nbr in adj[cur]:
                if nbr_price + price < all_prices[nbr]:
                    q.append((nbr_price + price, stops + 1, nbr))
                    all_prices[nbr] = price + nbr_price

        return all_prices[dst] if all_prices[dst] < math.inf else -1