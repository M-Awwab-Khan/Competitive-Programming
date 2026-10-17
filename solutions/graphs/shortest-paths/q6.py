from collections import defaultdict
from collections import deque


n = int(input())

g = defaultdict(list)

routes = defaultdict(list)

for i in range(n):
    arr  = list(map(int, input().split()))
    k = len(arr)
    for j in range(k):
        g[arr[j]].append([arr[(j + 1) % k], i])
        routes[arr[j]].append(i)
    

s, dest = map(int, input().split())

flag = False

ans = float("inf")

def bfs():
    global flag, ans

    if(s == dest):
        ans = 0
        flag = True
        return None

    q = deque()
    
    #print(routes[s])
    visited = set()
    for r in routes[s]:
        q.append([s, r, 1])
        visited.add((s, r))
    
    while(q):
        curr, currR, c = q.popleft()
        #print(curr, currR, c)

        

        if curr == dest:
            flag = True
            ans = min(ans, c)
            continue
            # print(c)
            # return


        for v, r in g[curr]:
            if (v, r) not in visited:
                visited.add((v, r))
                if(r == currR):
                    q.append([v, currR, c])
                else:
                    q.append([v, r, c+1])


bfs()

if(not flag):
    print(-1)
else:
    print(ans)