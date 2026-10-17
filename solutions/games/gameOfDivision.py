t = int(input())
def gameOfDivision(n, k, a):
    modGroups = {}
    for i in range(n):
        modValue = a[i] % k
        if modValue not in modGroups:
            modGroups[modValue] = []
        modGroups[modValue].append(i + 1)


    for key in modGroups:
        if len(modGroups[key]) == 1:
            return "YES\n" + str(modGroups[key][0])
    return "NO"

results = []
for _ in range(t):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    results.append(gameOfDivision(n, k, a))

print("\n".join(results))
