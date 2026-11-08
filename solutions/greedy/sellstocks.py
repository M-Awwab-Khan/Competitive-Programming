t = int(input())
while t:
    t -= 1
    k = int(input())
    n = int(input())
    prices = list(map(int, input().split()))

    profits = []
        
    for i in range(1, len(prices)):
        if prices[i] > prices[i-1]:
            profits.append(prices[i] - prices[i-1])
    
    profits.sort(reverse=True)
    print(sum(profits[:k]))