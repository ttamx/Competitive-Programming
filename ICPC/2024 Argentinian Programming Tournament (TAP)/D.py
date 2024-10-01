a=[*map(int,input().split())]
a.sort()
print("S" if a[2]>=a[1]+a[0] else "N")
